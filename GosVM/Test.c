/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS 许可证
 * @file    Test.c
 * @brief   GosVM Test C Source File \n
 * Copyright (c) 2020-2021 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include "GosVM.h"
#include "Stack.h"

int main()
{
	unsigned long long Code[] = { GosVM_call ,0ull };
	unsigned long long Data[] = { 0ull };

	int ret = GosVMRun(Code, sizeof(Code) / 8, Data, sizeof(Data) / 8, 1024);

	//printf("%d\n",ret);

	return 0;
}