#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>

int main(){
	using std::cout;
	using std::cin;
	using std::endl;
	int p = -1;
	int q = -1;
	bool running = 1;
	char ifContinue = 'y';
	while (running) {
		printf("***************************************\n");  //����
		printf("**                                   **\n");
		printf("**        ��ӭ�����߼��������       **\n");
		printf("**                                   **\n");
		printf("***************************************\n\n");

		printf("\n  ������P��ֵ��0��1��,�Իس�����:");
		cin >> p;  //��ȡP��ֵ
		while (p != 0 && p != 1)
		{
			printf("\n  P��ֵ��������,����������!");
			std::this_thread::sleep_for(std::chrono::seconds(2));//��Ϣ2s
			printf("\n  ������P��ֵ��0��1��,�Իس�����:");
			cin >> p;	
		}
		printf("\n  ������Q��ֵ��0��1��,�Իس�����:");
		cin >> q;  //��ȡQ��ֵ
		while (q != 0 && q != 1)
		{
			printf("\n  Q��ֵ��������,����������!");
			std::this_thread::sleep_for(std::chrono::seconds(2));//��Ϣ2s
			printf("\n  ������Q��ֵ��0��1��,�Իس�����:");
			cin >> q;
		}
		//����߼�������
		cout << endl;
		printf("��ȡ:\n\tP/\\Q = %d\n", p && q);
		printf("��ȡ:\n\tP\\/Q = %d\n", p || q);
		printf("����:\n\tP->Q = %d\n", (!p) || q);
		printf("����:\n\tP<->Q = %d\n", ((!p) || q) && ((!q) || p));
		//�Ƿ����
		cout << endl;
		printf("�Ƿ��������?(y/n)");
		cin >> ifContinue;
		while (ifContinue != 'y' && ifContinue != 'n') {
			printf("�������,����������!\n");
			std::this_thread::sleep_for(std::chrono::seconds(2));//��Ϣ2s
			printf("�Ƿ��������?(y/n)");
			cin >> ifContinue;
		}
		if (ifContinue == 'n') {
			running = 0;
		}
		else {
			system("cls");
		}
	}

	printf("��ӭ�´��ٴ�ʹ��!");
	system("pause");
	return 0;
}