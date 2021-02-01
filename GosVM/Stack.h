/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS ���֤
 * @file    Stack.h
 * @brief   Stack C Head File \n
 * Copyright (c) 2020-2021 GOSCPS ��������Ȩ��.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef  _GOSVM_STACK_H_
#define _GOSVM_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

	/**
	 * @brief ��ָ�����
	*/
#define _GOSVM_PTR_WAS_NULL_ 2

	/**
	 * @brief ջ����
	*/
#define _GOSVM_STACK_TOP_ 3

	/**
	 * @brief ջ����
	*/
#define _GOSVM_STACK_MAX_ 4

	/**
	 * @brief ��ջ�ṹ
	*/
	typedef struct GosVMStack
	{
		/**
		 * @brief �������
		*/
		int ErrorCode;

		/**
		 * @brief ��ջ��С
		*/
		unsigned long long StackSize;

		/**
		 * @brief ջ��ָ��
		*/
		unsigned long long* StackTop;

		/**
		 * @brief Ŀǰ��ջָ��
		*/
		unsigned long long* StackNow;
	}GosVMStack;

	/**
	 * @brief	��ȡGosVMStack
	 * @param	Size ջ��С
	 * @return	�µ�GosVMStack
	*/
	GosVMStack* GetGosVMStack(unsigned long long Size);

	/**
	 * @brief GosVMStack��Push����
	 * @param stack ջָ��
	 * @param data push������
	 * @return
	 * 0					�����ɹ� \n
	 * _GOSVM_STACK_MAX_	��ջ��� \n
	 * _GOSVM_PTR_WAS_NULL_ stackָ��ΪNULL \n
	*/
	int GosVMStackPush(GosVMStack* stack, unsigned long long data);

	/**
	 * @brief GosVMStack��Pop����
	 * @param stack stack ջָ��
	 * @param result �����ɹ����ص����ݵ�ַ
	 * @return
	 * _GOSVM_PTR_WAS_NULL_ stackΪ�� \n
	 * _GOSVM_STACK_TOP_	Ŀǰ��ջ��
	*/
	int GosVMStackPop(GosVMStack* stack, unsigned long long* result);

	/**
	 * @brief �ͷ�ջ
	 * @param stack Ҫ�ͷŵ�ջ
	*/
	void FreeGosVMStack(GosVMStack* stack);

#ifdef __cplusplus
}
#endif

#endif // ! _GOSVM_STACK_H_