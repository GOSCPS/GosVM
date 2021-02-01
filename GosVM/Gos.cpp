/** * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author GOSCPS
 * @license GOSCPS 许可证
 * @file    Gos.cpp
 * @brief   GosVM Front End C Source File \n
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

int main(int argc,char* argv[])
{
	if (argc < 2) {
		printf("No Input File!\n");
	}
	if (argc >= 4) {
		printf("Too Many Arguments!\n");
	}

	ifstream ifs;
	ifs.open(argv[1]);

	if (!(ifs.is_open() && ifs.good())) {
		cout << "File Open Error " << endl;
		return -1;
	}

	string line;
	
	vector<unsigned long long> code;
	vector<unsigned long long> data;

	vector<unsigned long long>* NowPush = nullptr;

	while (ifs >> line) {
		if (line == "Code:") {
			NowPush = &code;
		}
		else if (line == "Data:") {
			NowPush = &data;
		}
		else if (NowPush == nullptr) {
			cout << "Error:Not Specify Data Space" << endl;
			break;
		}

		if (line == "NOP") {
			NowPush->push_back(GosVM_nop);
		}
		else if (line == "PUSH") {
			NowPush->push_back(GosVM_push);
		}
		else if (line == "POP") {
			NowPush->push_back(GosVM_pop);
		}
		else if (line == "TOP") {
			NowPush->push_back(GosVM_top);
		}
		else if (line == "CALL") {
			NowPush->push_back(GosVM_call);
		}
		else if (line == "RET") {
			NowPush->push_back(GosVM_ret);
		}
		else if (line == "JMP") {
			NowPush->push_back(GosVM_jmp);
		}
		else if (line == "JMPT") {
			NowPush->push_back(GosVM_jmp_true);
		}
		else if (line == "ADD") {
			NowPush->push_back(GosVM_add);
		}
		else if (line == "MUL") {
			NowPush->push_back(GosVM_mul);
		}
		else if (line == "DIV") {
			NowPush->push_back(GosVM_div);
		}
		else if (line == "NOT") {
			NowPush->push_back(GosVM_not);
		}
		else if (line == "AND") {
			NowPush->push_back(GosVM_and);
		}
		else if (line == "OR") {
			NowPush->push_back(GosVM_or);
		}
		else if (line == "XOR") {
			NowPush->push_back(GosVM_xor);
		}
		else if (line == "EQU") {
			NowPush->push_back(GosVM_equal);
		}
		else if (line == "BIG") {
			NowPush->push_back(GosVM_bigger);
		}
		else if (line == "LFT") {
			NowPush->push_back(GosVM_lft);
		}
		else if (line == "RGT") {
			NowPush->push_back(GosVM_rgt);
		}
		else {
			NowPush->push_back(atoll(line.c_str()));
		}
	}

	ofstream binOut;
	binOut.open(argv[2], ios::out | ios::binary | ios::ate);

	if (!(binOut.is_open() && binOut.good())) {
		cout << "File Open Error " << endl;
		return -1;
	}

	//CodeSize + Code[]
	binOut.write((char*)code.size(),sizeof(unsigned long long));
	
	for (auto codeIt = code.cbegin(); codeIt != code.cend(); codeIt++) {
		binOut.write((char*)*codeIt, sizeof(unsigned long long));
	}

	//DataSize + data[]
	binOut.write((char*)data.size(), sizeof(unsigned long long));

	for (auto dataIt = data.cbegin(); dataIt != data.cend(); dataIt++) {
		binOut.write((char*)*dataIt, sizeof(unsigned long long));
	}

	ifs.close();
	binOut.close();
	return 0;
}