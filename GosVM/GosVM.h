/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS 许可证
 * @file    GosVM.h
 * @brief   GosVM C Head File \n
 * Copyright (c) 2020-2021 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _GOSVM_GOSVM_H_
#define _GOSVM_GOSVM_H_

#include "Stack.h"

 /**
  * @brief 自动访问越界检测
 */
#define _GosVM_SafeAccessNext(_Instructions,_pc) \
{if ((_pc + 1) >= _Instructions) return _GOSVM_MISSING_OPERAND_;}

/**
 * @brief 虚拟机初始化错误:实例指针为空
*/
#define _GOSVM_START_ERROR_PTR_WAS_NULL_ 10

/**
 * @brief 虚拟机错误:未知指令
*/
#define _GOSVM_UNKNOWN_COMMAND_ 11

/**
 * @brief 虚拟机错误:缺少操作数
*/
#define _GOSVM_MISSING_OPERAND_ 12

/**
 * @brief 虚拟机错误:堆栈错误
*/
#define _GOSVM_STACK_ERROR_ 13

/**
 * @brief 虚拟机错误:错误的地址
*/
#define _GOSVM_ADDRESS_ERROR_ 14

/**
 * @brief 指令集
 * 指令 [操作数]
*/
typedef enum GosVMInstructionSet
{
	GosVM_nop = 0,			/**< 什么都不干			*/
	GosVM_push = 1,			/**< 入栈		[地址]	*/
	GosVM_pop = 2,			/**< 出栈		[地址]	*/
	GosVM_top = 3,			/**< 跳转到栈顶			*/
	GosVM_call,				/**< 调用		[地址]	*/
	GosVM_ret,				/**< 返回				*/
	GosVM_jmp,				/**< 跳转		[地址]	*/
	GosVM_jmp_true,			/**< 为真跳转		[地址]	*/
	GosVM_jmp_false,		/**< 为假跳转		[地址]	*/
	GosVM_jmp_equal,		/**< 等于则跳转	[地址]	*/
	GosVM_jmp_not_equal,	/**< 不等于则跳转 [地址]	*/
	GosVM_jmp_bigger,		/**< 大于则跳转	[地址]	*/
	GosVM_jmp_smaller,		/**< 小于则跳转	[地址]	*/
	GosVM_add,				/**< 栈相加				*/
	GosVM_sub,				/**< 栈相减				*/
	GosVM_mul,				/**< 栈乘法				*/
	GosVM_div,				/**< 栈除法				*/
	GosVM_not,				/**< 逻辑非				*/
	GosVM_and,				/**< 逻辑与				*/
	GosVM_or,				/**< 逻辑或				*/
	GosVM_xor,				/**< 逻辑异或				*/
}GosVMInstructionSet;

/**
 * @brief 指令列表
*/
typedef struct GosVMInstructions
{
	/**
	 * @brief 指令地址
	*/
	unsigned long long* InstructionAddress;

	/**
	 * @brief 指令长度
	*/
	unsigned long long InstructionLength;
}GosVMInstructions;

/**
 * @brief 数据列表
*/
typedef struct GosVMDatas {
	/**
	 * @brief 数据地址
	*/
	unsigned long long* DataAddress;

	/**
	 * @brief 数据地址长度
	*/
	unsigned long long DataLength;
}GosVMDatas;

/**
 * @brief GosVM实例数据
*/
typedef struct GosVMInstance {
	/**
	 * @brief 代码区
	*/
	GosVMInstructions* Instructions;

	/**
	 * @brief 数据区
	*/
	GosVMDatas* Datas;

	/**
	 * @brief 堆栈
	*/
	GosVMStack* Stack;
}GosVMInstance;

int GosVMRun(
	unsigned long long* Code,
	unsigned long long CodeSize,
	unsigned long long* Data,
	unsigned long long DataSize,
	unsigned long long StackSize);

#endif // ! _GOSVM_GOSVM_H_