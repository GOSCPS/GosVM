/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS 许可证
 * @file    VM.cpp
 * @brief   VM C Source File \n
 * Copyright (c) 2020-2021 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "GosVM.h"
#include "Stack.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Arguments Count Error!" << endl;
	}

	ifstream ifs;
	ifs.open(argv[1], ios::binary | ios::in);

	unsigned long long CodeSize;

	ifs >> CodeSize;

	unsigned long long* code = new unsigned long long[CodeSize];
	for (unsigned long long ptr = 0; ptr < CodeSize; ptr++) {
		ifs >> *(code + ptr);
	}

	unsigned long long DataSize;

	ifs >> DataSize;

	unsigned long long* data = new unsigned long long[DataSize];
	for (unsigned long long ptr = 0; ptr < DataSize; ptr++) {
		ifs >> *(data + ptr);
	}

	GosVMRun(code, CodeSize, data, DataSize, 4096);

	return 0;
}