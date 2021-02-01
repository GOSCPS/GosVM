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
#include <cerrno>
#include "GosVM.h"
#include "Stack.h"

using namespace std;

int main(int argc,char* argv[])
{
	if (argc != 3) {
		cout << "Usage Error" << endl;
	}

	ifstream ifs;
	ifs.open(argv[1]);

	if (!(ifs.is_open() && ifs.good())) {
		cout << "File Open Error " << errno << strerror(errno) <<  endl;
		return -1;
	}

	string line;
	
	vector<unsigned long long> code;
	vector<unsigned long long> data;

	vector<unsigned long long>* NowPush = nullptr;

	while (ifs >> line) {
		if (line == "Code:") {
			NowPush = &code;
			continue;
		}
		else if (line == "Data:") {
			NowPush = &data;
			continue;
		}
		if (NowPush == nullptr) {
			cout << "Error:Not Specify Data Space" << endl;
			return -1;
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
		else if (line == "IN") {
			NowPush->push_back(GosVM_in);
		}
		else if (line == "OUT") {
			NowPush->push_back(GosVM_out);
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
	unsigned long long size = code.size();
	binOut.write((char*)&size,sizeof(unsigned long long));
	
	for (auto codeIt = code.cbegin(); codeIt != code.cend(); codeIt++) {
		unsigned long long c = *codeIt;
		binOut.write((char*)&c, sizeof(unsigned long long));
	}

	//DataSize + Data[]
	
	size = data.size();
	binOut.write((char*)&size, sizeof(unsigned long long));

	for (auto dataIt = data.cbegin(); dataIt != data.cend(); dataIt++) {
		unsigned long long d = *dataIt;
		binOut.write((char*)&d, sizeof(unsigned long long));
	}

	ifs.close();
	binOut.close();
	return 0;
}