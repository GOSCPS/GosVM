/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS 许可证
 * @file    Stack.h
 * @brief   Stack C Head File \n
 * Copyright (c) 2020-2021 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef  _GOSVM_STACK_H_
#define _GOSVM_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

	/**
	 * @brief 空指针错误
	*/
#define _GOSVM_PTR_WAS_NULL_ 2

	/**
	 * @brief 栈到顶
	*/
#define _GOSVM_STACK_TOP_ 3

	/**
	 * @brief 栈到底
	*/
#define _GOSVM_STACK_MAX_ 4

	/**
	 * @brief 堆栈结构
	*/
	typedef struct GosVMStack
	{
		/**
		 * @brief 错误代码
		*/
		int ErrorCode;

		/**
		 * @brief 堆栈大小
		*/
		unsigned long long StackSize;

		/**
		 * @brief 栈顶指针
		*/
		unsigned long long* StackTop;

		/**
		 * @brief 目前堆栈指针
		*/
		unsigned long long* StackNow;
	}GosVMStack;

	/**
	 * @brief	获取GosVMStack
	 * @param	Size 栈大小
	 * @return	新的GosVMStack
	*/
	GosVMStack* GetGosVMStack(unsigned long long Size);

	/**
	 * @brief GosVMStack的Push操作
	 * @param stack 栈指针
	 * @param data push的数据
	 * @return
	 * 0					操作成功 \n
	 * _GOSVM_STACK_MAX_	堆栈溢出 \n
	 * _GOSVM_PTR_WAS_NULL_ stack指针为NULL \n
	*/
	int GosVMStackPush(GosVMStack* stack, unsigned long long data);

	/**
	 * @brief GosVMStack的Pop操作
	 * @param stack stack 栈指针
	 * @param result 操作成功返回的数据地址
	 * @return
	 * _GOSVM_PTR_WAS_NULL_ stack为空 \n
	 * _GOSVM_STACK_TOP_	目前在栈顶
	*/
	int GosVMStackPop(GosVMStack* stack, unsigned long long* result);

	/**
	 * @brief 释放栈
	 * @param stack 要释放的栈
	*/
	void FreeGosVMStack(GosVMStack* stack);

#ifdef __cplusplus
}
#endif

#endif // ! _GOSVM_STACK_H_