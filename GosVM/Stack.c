/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS 许可证
 * @file    Stack.c
 * @brief   Stack C Source File \n
 * Copyright (c) 2020-2021 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Stack.h"

/**
 * @brief	获取GosVMStack
 * @param	Size 栈大小
 * @return	新的GosVMStack
*/
GosVMStack* GetGosVMStack(unsigned long long Size) {
	GosVMStack* stack = calloc(1, sizeof(GosVMStack));

	if (stack == NULL)
		return NULL;

	stack->StackSize = Size;
	stack->StackTop = calloc(1, Size);
	stack->StackNow = stack->StackTop;

	return stack;
}

/**
 * @brief GosVMStack的Push操作
 * @param stack 栈指针
 * @param data push的数据
 * @return 
 * 0					操作成功 \n
 * _GOSVM_STACK_MAX_	堆栈溢出 \n
 * _GOSVM_PTR_WAS_NULL_ stack指针为NULL \n
*/
int GosVMStackPush(GosVMStack* stack, unsigned long long data) {
	if (stack == NULL) {
		return _GOSVM_PTR_WAS_NULL_;
	}

	if ((stack->StackTop + stack->StackSize) <= stack->StackNow) {
		stack->ErrorCode = _GOSVM_STACK_MAX_;
		return _GOSVM_STACK_MAX_;
	}

	*(stack->StackNow) = data;
	stack->StackNow++;

	return 0;
}

/**
 * @brief GosVMStack的Pop操作
 * @param stack stack 栈指针
 * @param result 操作成功返回的数据地址
 * @return 
 * _GOSVM_PTR_WAS_NULL_ stack为空 \n
 * _GOSVM_STACK_TOP_	目前在栈顶
*/
int GosVMStackPop(GosVMStack* stack, unsigned long long* result) {
	if (stack == NULL)
		return _GOSVM_PTR_WAS_NULL_;

	if (stack->StackNow == stack->StackTop) {
		stack->StackNow++;
	}
	
	stack->StackNow--;
	*result = *(stack->StackNow);
	

	return 0;
}