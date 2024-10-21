#include <iostream>
#include <cmath>
#include "Matrix.h"
using namespace std;

static void menu() {
	//输入行数,列数
	double dim = 0.0;
	while (1) {
		cout << "请输入关系矩阵的维数:";
		cin >> dim;
		if (cin.fail() || dim <= 0 || floor(dim) != dim) {
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "输入非法,请重新输入" << endl;
		}
		else {
			break;
		}
	}
	int dimension = static_cast<int>(dim);
	vector<vector<int>> matrix(dimension, vector<int>(dimension, 0));
	//输入关系矩阵
	for (int i = 0; i < dimension; i++) {
		cout << "请输入矩阵的第" << i + 1 << "行元素(空格分隔):";
		for (int j = 0; j < dimension; j++) {
			int temp = 0;
			cin >> temp;
			if (cin.fail() || (temp != 0 && temp != 1)) {
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "输入非法,请重新输入: " << endl;
				i--;
				break;
			}
			matrix[i][j] = temp;
		}
	}
	Matrix relation(matrix);
	cout << endl << "当前关系矩阵为: " << endl;
	relation.PrintMatrix();
	cout << endl;
	cout << "------------" << endl;
	cout << "1.求自反闭包" << endl;
	cout << "2.求对称闭包" << endl;
	cout << "3.求传递闭包" << endl;
	cout << "4.清屏" << endl;
	cout << "5.退出" << endl;

	bool cls = false;
	while (1) {
		if (cls) {
			cout << "当前关系矩阵为: " << endl;
			relation.PrintMatrix();
			cout << endl;
			cout << "------------" << endl;
			cout << "1.求自反闭包" << endl;
			cout << "2.求对称闭包" << endl;
			cout << "3.求传递闭包" << endl;
			cout << "4.清屏" << endl;
			cout << "5.退出" << endl;
			cls = false;
		}
		double choice = 0.0;
		while (1) {
			cout << "请选择操作:";
			cin >> choice;
			if (cin.fail() || choice < 1 || choice > 5 || floor(choice) != choice) {
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "输入非法,请重新输入" << endl;
			}
			else {
				break;
			}
		}
		int num = static_cast<int>(choice);
		if (num == 5) {
			cout << "程序结束" << endl;
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
				// 求自反闭包
				cout << "自反闭包为:" << endl;
				relation.GetReflexiveClosure().PrintMatrix();
				break;
			case 2:
				// 求对称闭包
				cout << "对称闭包为:" << endl;
				relation.GetSymmetricClosure().PrintMatrix();
				break;
			case 3:
				// 求传递闭包
				cout << "传递闭包为:" << endl;
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