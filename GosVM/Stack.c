/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS ���֤
 * @file    Stack.c
 * @brief   Stack C Source File \n
 * Copyright (c) 2020-2021 GOSCPS ��������Ȩ��.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Stack.h"

/**
 * @brief	��ȡGosVMStack
 * @param	Size ջ��С
 * @return	�µ�GosVMStack
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
 * @brief GosVMStack��Push����
 * @param stack ջָ��
 * @param data push������
 * @return 
 * 0					�����ɹ� \n
 * _GOSVM_STACK_MAX_	��ջ��� \n
 * _GOSVM_PTR_WAS_NULL_ stackָ��ΪNULL \n
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
 * @brief GosVMStack��Pop����
 * @param stack stack ջָ��
 * @param result �����ɹ����ص����ݵ�ַ
 * @return 
 * _GOSVM_PTR_WAS_NULL_ stackΪ�� \n
 * _GOSVM_STACK_TOP_	Ŀǰ��ջ��
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