/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS ���֤
 * @file    Gos.c
 * @brief   GosVM Front End C Source File \n
 * Copyright (c) 2020-2021 GOSCPS ��������Ȩ��.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <vector>
#include "GosVM.h"
#include "Stack.h"

using namespace std;

int main(int argc,char* argv[])
{
	if (argc == 1) {
		printf("No Input File!");
	}
	if (argc > 2) {
		printf("Too Many Arguments!");
	}

	FILE* file = fopen(argv[1], "r");


	fclose(file);

	return 0;
}