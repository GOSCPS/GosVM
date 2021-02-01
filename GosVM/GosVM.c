/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS 许可证
 * @file    GosVM.c
 * @brief   GosVM mainly Source File \n
 * Copyright (c) 2020-2021 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "GosVM.h"
#ifdef __cplusplus
extern "C"	{
#endif

/**
 * @brief 运行代码
 * @param Code		代码指针
 * @param CodeSize  代码长度
 * @param Data		数据指针
 * @param DataSize	数据长度
 * @param StackSize	堆栈大小
 * @return 
*/
int GosVMRun(
	unsigned long long* Code,
	unsigned long long CodeSize,
	unsigned long long* Data,
	unsigned long long DataSize,
	unsigned long long StackSize) {

	//初始化数据
	GosVMInstructions codes;
	codes.InstructionAddress = Code;
	codes.InstructionLength = CodeSize;

	GosVMDatas datas;
	datas.DataAddress = Data;
	datas.DataLength = DataSize;

	GosVMStack* stack = GetGosVMStack(StackSize);

	GosVMInstance vm;
	vm.Datas = &datas;
	vm.Instructions = &codes;
	vm.Stack = stack;
	
	int result = _GosVMRunInstance(vm);
	FreeGosVMStack(stack);

	return result;
}

/**
 * @brief 运行虚拟机实例
 * @param Instance 实例
 * @return 
 * 返回0虚拟机执行成功 \n
 * 否则返回错误代码
*/
int _GosVMRunInstance(GosVMInstance Instance) {
	if (Instance.Datas == NULL
		|| Instance.Instructions == NULL
		|| Instance.Stack == NULL) {
		return _GOSVM_START_ERROR_PTR_WAS_NULL_;
	}

	//程序计数器
	unsigned long long pc = 0;

	while (Instance.Instructions->InstructionLength > pc) {
		switch (*(Instance.Instructions->InstructionAddress + pc))
		{
		case GosVM_nop:
			break;
		case GosVM_push:
			_GosVM_SafeAccessNext(Instance.Instructions->InstructionLength, pc);

			//Push栈
			pc++;
			if (GosVMStackPush(Instance.Stack, *(Instance.Instructions->InstructionAddress + pc)) != 0) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_pop:
			_GosVM_SafeAccessNext(Instance.Instructions->InstructionLength, pc);

			//Pop栈，把数据放入数据区
			pc++;
			if (GosVMStackPop(Instance.Stack, (
				Instance.Datas->DataAddress + 
				(*(Instance.Instructions->InstructionAddress+pc)))) != 0) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_top:
			Instance.Stack->StackNow = Instance.Stack->StackTop;
			break;

		case GosVM_call:
			_GosVM_SafeAccessNext(Instance.Instructions->InstructionLength, pc);
			pc++;

			//获取call地址并检查是否在Code范围内
			unsigned long long GosVM_call_address = (*(Instance.Instructions->InstructionAddress + pc));
			if (GosVM_call_address >= Instance.Instructions->InstructionLength) {
				return _GOSVM_ADDRESS_ERROR_;
			}
			else {
				//将返回地址打入栈中
				if (GosVMStackPush(Instance.Stack, GosVM_call_address)) {
					return _GOSVM_STACK_ERROR_;
				}
				pc = GosVM_call_address;

				//抵消++
				pc--;
			}
			break;

		case GosVM_ret:
			;
			unsigned long long GosVM_ret_address = 0;
			
			if (GosVMStackPop(Instance.Stack, &GosVM_ret_address)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVM_ret_address >= Instance.Instructions->InstructionLength) {
				return _GOSVM_ADDRESS_ERROR_;
			}
			pc = GosVM_ret_address;
			pc--;

			break;

		case GosVM_jmp:
			_GosVM_SafeAccessNext(Instance.Instructions->InstructionLength, pc);
			pc++;

			unsigned long long GosVM_jmp_address = *(Instance.Instructions->InstructionAddress + pc);
			if (GosVM_jmp_address >= Instance.Instructions->InstructionLength) {
				return _GOSVM_ADDRESS_ERROR_;
			}

			pc = GosVM_jmp_address;
			pc--;

			break;

		case GosVM_jmp_true:
			_GosVM_SafeAccessNext(Instance.Instructions->InstructionLength, pc);
			pc++;

			unsigned long long GosVM_jmp_true_address = *(Instance.Instructions->InstructionAddress + pc);
			unsigned long long GosVM_jmp_true_data = 0;

			if (GosVMStackPop(Instance.Stack, &GosVM_jmp_true_data)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVM_jmp_true_data) {
				if (GosVM_jmp_true_address >= Instance.Instructions->InstructionLength) {
					return _GOSVM_ADDRESS_ERROR_;
				}
				pc = GosVM_jmp_true_address;
				pc--;
			}

			break;

		case GosVM_add:
			;
			unsigned long long GosVM_add_first = 0;
			unsigned long long GosVM_add_second = 0;

			if (GosVMStackPop(Instance.Stack, &GosVM_add_first)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPop(Instance.Stack, &GosVM_add_second)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPush(Instance.Stack, GosVM_add_first + GosVM_add_second)) {
				return _GOSVM_STACK_ERROR_;
			}

			break;
		case GosVM_mul:
			;
			unsigned long long GosVM_mul_first = 0;
			unsigned long long GosVM_mul_second = 0;

			if (GosVMStackPop(Instance.Stack, &GosVM_mul_first)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPop(Instance.Stack, &GosVM_mul_second)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPush(Instance.Stack, GosVM_mul_first * GosVM_mul_second)) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_div:
			;
			unsigned long long GosVM_div_first = 0;
			unsigned long long GosVM_div_second = 0;

			if (GosVMStackPop(Instance.Stack, &GosVM_div_first)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPop(Instance.Stack, &GosVM_div_second)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPush(Instance.Stack, GosVM_div_first / GosVM_div_second)) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_not:
			;
			unsigned long long GosVM_not_ = 0;

			if (GosVMStackPop(Instance.Stack, &GosVM_not_)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPush(Instance.Stack, ~GosVM_not_)) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_and:
			;
			unsigned long long GosVM_and_first = 0;
			unsigned long long GosVM_and_second = 0;

			if (GosVMStackPop(Instance.Stack, &GosVM_and_first)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPop(Instance.Stack, &GosVM_and_second)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPush(Instance.Stack, GosVM_and_first & GosVM_and_second)) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_or:
			;
			unsigned long long GosVM_or_first = 0;
			unsigned long long GosVM_or_second = 0;

			if (GosVMStackPop(Instance.Stack, &GosVM_or_first)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPop(Instance.Stack, &GosVM_or_second)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPush(Instance.Stack, GosVM_or_first | GosVM_or_second)) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_xor:
			;
			unsigned long long GosVM_xor_first = 0;
			unsigned long long GosVM_xor_second = 0;

			if (GosVMStackPop(Instance.Stack, &GosVM_xor_first)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPop(Instance.Stack, &GosVM_xor_second)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPush(Instance.Stack, GosVM_xor_first ^ GosVM_xor_second)) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_equal:
			;
			unsigned long long GosVM_equal_first = 0;
			unsigned long long GosVM_equal_second = 0;

			if (GosVMStackPop(Instance.Stack, &GosVM_equal_first)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPop(Instance.Stack, &GosVM_equal_second)) {
				return _GOSVM_STACK_ERROR_;
			}

			unsigned long long GosVM_equal_result = 0;
			if (GosVM_equal_first == GosVM_equal_second)
				GosVM_equal_result = 1;

			if (GosVMStackPush(Instance.Stack, GosVM_equal_result)) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_bigger:
			;
			unsigned long long GosVM_bigger_first = 0;
			unsigned long long GosVM_bigger_second = 0;

			if (GosVMStackPop(Instance.Stack, &GosVM_bigger_first)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPop(Instance.Stack, &GosVM_bigger_second)) {
				return _GOSVM_STACK_ERROR_;
			}

			unsigned long long GosVM_bigger_result = 0;
			if (GosVM_bigger_first > GosVM_bigger_second)
				GosVM_bigger_result = 1;

			if (GosVMStackPush(Instance.Stack, GosVM_bigger_result)) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_lft:
			_GosVM_SafeAccessNext(Instance.Instructions->InstructionLength, pc);
			pc++;

			unsigned long long GosVM_lft_source = 0;
			unsigned long long GosVM_lft_count = *(Instance.Instructions->InstructionAddress + pc);

			if (GosVMStackPop(Instance.Stack, &GosVM_lft_source)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPush(Instance.Stack, GosVM_lft_source << GosVM_lft_count)) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		case GosVM_rgt:
			_GosVM_SafeAccessNext(Instance.Instructions->InstructionLength, pc);
			pc++;

			unsigned long long GosVM_rgt_source = 0;
			unsigned long long GosVM_rgt_count = *(Instance.Instructions->InstructionAddress + pc);

			if (GosVMStackPop(Instance.Stack, &GosVM_rgt_source)) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVMStackPush(Instance.Stack, GosVM_rgt_source >> GosVM_rgt_count)) {
				return _GOSVM_STACK_ERROR_;
			}
			break;

		//TODO:IN
		//DOTO:OUT

		default:
			return _GOSVM_UNKNOWN_COMMAND_;
		}

		pc++;
	}

	return 0;
}

#ifdef __cplusplus
}
#endif