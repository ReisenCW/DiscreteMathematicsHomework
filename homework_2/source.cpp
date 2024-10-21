#include <iostream>
#include <string>
using namespace std;
#define __DEBUG 0

/*
���Ż�:
A:ӪҵԱA͵���ֱ�
B:ӪҵԱB͵���ֱ�
C:��������Ӫҵʱ��
D:B�ṩ��֤����ȷ
E:����δ����
*/

/*
����:
��1��ӪҵԱA��B͵���ֱ�						A �� B    A || B
��2����A����������������Ӫҵʱ�䣻				A �� C	 !A || C
��3����B�ṩ��֤����ȷ�������δ������			D �� E	 !D || E 
��4����B�ṩ��֤�ݲ���ȷ��������������Ӫҵʱ�䣻!D �� !C  D || !C
��5��������������								!E       !E
*/

//�߼�����
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
	//����
	bool rule1 = logicOperate(A, B, "\//");
	bool rule2 = logicOperate(A, C, "->");
	bool rule3 = logicOperate(D, E, "->");
	bool rule4 = logicOperate(logicOperate(D,'!'), logicOperate(C, '!'), "->");
	bool rule5 = logicOperate(E,'!');

	//������
	bool result = rule1 && rule2 && rule3 && rule4 && rule5;
	return result;
}

int main() {
	 //�������п��ܵ����
	int currentCase = 0;//��ǰ�ǵڼ��ֿ�����
	for (int i = 0; i < 32; ++i) {
		//iÿ��ѭ��++,ʹ�ø��������Ԫȡ0,1�����ȫ������
		bool A = i & 1;//ȡi�Ķ����Ʊ�ʾ�����λ
		bool B = i & 2;//ȡi�Ķ����Ʊ�ʾ�Ĵε�λ
		bool C = i & 4;//ȡi�Ķ����Ʊ�ʾ�ĵ���λ
		bool D = i & 8;//ȡi�Ķ����Ʊ�ʾ�ĵ���λ
		bool E = i & 16;//ȡi�Ķ����Ʊ�ʾ�����λ
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