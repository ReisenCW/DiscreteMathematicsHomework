#include <iostream>
#include <string>
using namespace std;
#define __DEBUG 0

/*
符号化:
A:营业员A偷了手表
B:营业员B偷了手表
C:作案不在营业时间
D:B提供的证据正确
E:货柜未上锁
*/

/*
推理:
（1）营业员A或B偷了手表；						A ∨ B    A || B
（2）若A作案，则作案不在营业时间；				A → C	 !A || C
（3）若B提供的证据正确，则货柜未上锁；			D → E	 !D || E 
（4）若B提供的证据不正确，则作案发生在营业时间；!D → !C  D || !C
（5）货柜上了锁。								!E       !E
*/

//逻辑运算
bool logicOperate(bool a, bool b, string op) {
	if (op == "\//") {
		return a || b;
	}
	else if(op == "->") {
		return !a || b;
	}
	else {
		cerr << "Error: Invalid operator!" << endl;
		return false;
	}
}

bool logicOperate(bool a, string op) {
	if (op == "!") {
		return !a;
	}
	else {
		cerr << "Error: Invalid operator!" << endl;
		return false;
	}
}

bool logicOperate(bool a, char op) {
	if (op == '!') {
		return !a;
	}
	else {
		cerr << "Error: Invalid operator!" << endl;
		return false;
	}
}

bool logicInference(bool A, bool B, bool C, bool D, bool E) {
	//条件
	bool rule1 = logicOperate(A, B, "\//");
	bool rule2 = logicOperate(A, C, "->");
	bool rule3 = logicOperate(D, E, "->");
	bool rule4 = logicOperate(logicOperate(D,'!'), logicOperate(C, '!'), "->");
	bool rule5 = logicOperate(E,'!');

	//推理结果
	bool result = rule1 && rule2 && rule3 && rule4 && rule5;
	return result;
}

int main() {
	 //遍历所有可能的情况
	int currentCase = 0;//当前是第几种可能性
	for (int i = 0; i < 32; ++i) {
		//i每次循环++,使得各个命题变元取0,1的组合全部遍历
		bool A = i & 1;//取i的二进制表示的最低位
		bool B = i & 2;//取i的二进制表示的次低位
		bool C = i & 4;//取i的二进制表示的第三位
		bool D = i & 8;//取i的二进制表示的第四位
		bool E = i & 16;//取i的二进制表示的最高位
		if (logicInference(A, B, C, D, E)) {
			cout << "Case " << ++currentCase << ": ";
			cout << "A= " << A << "\t";
			cout << "B= " << B << endl;
#if __DEBUG
			cout << "\tC= " << C << "\t";
			cout << "D= " << D << "\t";
			cout << "E= " << E << endl;
#endif
			cout << endl;
		}
	}
	return 0;
}