/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS 许可证
 * @file    GosVM.c
 * @brief   GosVM mainly Source File \n
 * Copyright (c) 2020-2021 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "GosVM.h"

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
	
	return _GosVMRunInstance(vm);
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
				if (GosVMStackPush(Instance.Stack, GosVM_call_address) != 0) {
					return _GOSVM_STACK_ERROR_;
				}
				pc = GosVM_call_address;

				//抵消++
				pc--;
			}
			break;

		case GosVM_ret:
			;
			unsigned long long GosVM_ret_address;
			
			if (GosVMStackPop(Instance.Stack, &GosVM_ret_address) != 0) {
				return _GOSVM_STACK_ERROR_;
			}

			if (GosVM_ret_address >= Instance.Instructions->InstructionLength) {
				return _GOSVM_ADDRESS_ERROR_;
			}
			pc = GosVM_ret_address;
			pc--;

			break;
		default:
			return _GOSVM_UNKNOWN_COMMAND_;
		}

		pc++;
	}

	return 0;
}