#include <iostream>
#include <cmath>
#include "Matrix.h"
using namespace std;

static void menu() {
	//��������,����
	double dim = 0.0;
	while (1) {
		cout << "�������ϵ�����ά��:";
		cin >> dim;
		if (cin.fail() || dim <= 0 || floor(dim) != dim) {
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "����Ƿ�,����������" << endl;
		}
		else {
			break;
		}
	}
	int dimension = static_cast<int>(dim);
	vector<vector<int>> matrix(dimension, vector<int>(dimension, 0));
	//�����ϵ����
	for (int i = 0; i < dimension; i++) {
		cout << "���������ĵ�" << i + 1 << "��Ԫ��(�ո�ָ�):";
		for (int j = 0; j < dimension; j++) {
			int temp = 0;
			cin >> temp;
			if (cin.fail() || (temp != 0 && temp != 1)) {
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "����Ƿ�,����������: " << endl;
				i--;
				break;
			}
			matrix[i][j] = temp;
		}
	}
	Matrix relation(matrix);
	cout << endl << "��ǰ��ϵ����Ϊ: " << endl;
	relation.PrintMatrix();
	cout << endl;
	cout << "------------" << endl;
	cout << "1.���Է��հ�" << endl;
	cout << "2.��ԳƱհ�" << endl;
	cout << "3.�󴫵ݱհ�" << endl;
	cout << "4.����" << endl;
	cout << "5.�˳�" << endl;

	bool cls = false;
	while (1) {
		if (cls) {
			cout << "��ǰ��ϵ����Ϊ: " << endl;
			relation.PrintMatrix();
			cout << endl;
			cout << "------------" << endl;
			cout << "1.���Է��հ�" << endl;
			cout << "2.��ԳƱհ�" << endl;
			cout << "3.�󴫵ݱհ�" << endl;
			cout << "4.����" << endl;
			cout << "5.�˳�" << endl;
			cls = false;
		}
		double choice = 0.0;
		while (1) {
			cout << "��ѡ�����:";
			cin >> choice;
			if (cin.fail() || choice < 1 || choice > 5 || floor(choice) != choice) {
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "����Ƿ�,����������" << endl;
			}
			else {
				break;
			}
		}
		int num = static_cast<int>(choice);
		if (num == 5) {
			cout << "�������" << endl;
			return;
		}
		if (num == 4) {
			system("cls");
			cls = true;
			continue;
		}
		cout << endl;
		switch (num) {
			case 1:
				// ���Է��հ�
				cout << "�Է��հ�Ϊ:" << endl;
				relation.GetReflexiveClosure().PrintMatrix();
				break;
			case 2:
				// ��ԳƱհ�
				cout << "�ԳƱհ�Ϊ:" << endl;
				relation.GetSymmetricClosure().PrintMatrix();
				break;
			case 3:
				// �󴫵ݱհ�
				cout << "���ݱհ�Ϊ:" << endl;
				relation.GetTransitiveClosure().PrintMatrix();
				break;
			default:
				break;
		}
	}
}

int main() {
	menu();
	return 0;
}