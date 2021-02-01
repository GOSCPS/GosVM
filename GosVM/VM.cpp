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

	if (!(ifs.is_open() && ifs.good())) {
		cout << "File Open Error" << endl;
		return -1;
	}

	unsigned long long CodeSize = 0;

	ifs.read((char*)&CodeSize, sizeof(unsigned long long));

	unsigned long long* code = new unsigned long long[CodeSize];

	for (unsigned long long ptr = 0; ptr < CodeSize; ptr++) {
		ifs.read((char*)(code + ptr), sizeof(unsigned long long));
	}

	unsigned long long DataSize = 0;

	ifs.read((char*)&DataSize, sizeof(unsigned long long));

	unsigned long long* data = new unsigned long long[DataSize];
	for (unsigned long long ptr = 0; ptr < DataSize; ptr++) {
		ifs.read((char*)(data + ptr), sizeof(unsigned long long));
	}

	int result = GosVMRun(code, CodeSize, data, DataSize, 4096);

	delete[] code;
	delete[] data;

	return result;
}