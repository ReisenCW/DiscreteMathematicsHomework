#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <chrono>
#include "functions.h"
#include <set>

int main() {
	//ֻ�ж���Ӣ��״̬�µ������
	using std::cout;
	using std::cin;
	using std::endl;
	using std::string;
	string formula;
	std::set<char> varSet;
	printf("***************************************\n");  //����
	printf("**                                   **\n");
	printf("**         ��ӭ�����߼��������      **\n");
	printf("**   (��������ֵ��,����ʽ,֧������)  **\n");
	printf("**                                   **\n");
	printf("**              ��!��ʾ��            **\n");
	printf("**              ��&��ʾ��            **\n");
	printf("**              ��|��ʾ��            **\n");
	printf("**             ��^��ʾ�̺�           **\n");
	printf("**             ��~��ʾ��ֵ           **\n");
	printf("**                                   **\n");
	printf("***************************************\n\n");
	printf("������һ���Ϸ������⹫ʽ:\n");  //����ʽ��
	getline(cin, formula);
	while(!checkLeagal(formula)) {//�ж������Ƿ�Ϸ�
		printf("�������,����������:\n");
		std::this_thread::sleep_for(std::chrono::seconds(2));//��Ϣ2s
		printf("������һ���Ϸ������⹫ʽ:\n");
		getline(cin, formula);
	}
	//ȥ���ո�
	deleteSpace(formula);
	
	//�����������,���ѱ�������set��
	cout << endl;
	printf("��ʽ���еı�������Ϊ: %d\n", setVar(formula, varSet));

	//������
	printResult(formula, varSet);


	system("pause");
	return 0;
}