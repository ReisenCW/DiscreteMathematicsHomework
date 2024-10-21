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
		printf("***************************************\n");  //标语
		printf("**                                   **\n");
		printf("**        欢迎进入逻辑运算程序       **\n");
		printf("**                                   **\n");
		printf("***************************************\n\n");

		printf("\n  请输入P的值（0或1）,以回车结束:");
		cin >> p;  //读取P的值
		while (p != 0 && p != 1)
		{
			printf("\n  P的值输入有误,请重新输入!");
			std::this_thread::sleep_for(std::chrono::seconds(2));//休息2s
			printf("\n  请输入P的值（0或1）,以回车结束:");
			cin >> p;	
		}
		printf("\n  请输入Q的值（0或1）,以回车结束:");
		cin >> q;  //读取Q的值
		while (q != 0 && q != 1)
		{
			printf("\n  Q的值输入有误,请重新输入!");
			std::this_thread::sleep_for(std::chrono::seconds(2));//休息2s
			printf("\n  请输入Q的值（0或1）,以回车结束:");
			cin >> q;
		}
		//输出逻辑运算结果
		cout << endl;
		printf("合取:\n\tP/\\Q = %d\n", p && q);
		printf("析取:\n\tP\\/Q = %d\n", p || q);
		printf("条件:\n\tP->Q = %d\n", (!p) || q);
		printf("条件:\n\tP<->Q = %d\n", ((!p) || q) && ((!q) || p));
		//是否继续
		cout << endl;
		printf("是否继续运算?(y/n)");
		cin >> ifContinue;
		while (ifContinue != 'y' && ifContinue != 'n') {
			printf("输入错误,请重新输入!\n");
			std::this_thread::sleep_for(std::chrono::seconds(2));//休息2s
			printf("是否继续运算?(y/n)");
			cin >> ifContinue;
		}
		if (ifContinue == 'n') {
			running = 0;
		}
		else {
			system("cls");
		}
	}

	printf("欢迎下次再次使用!");
	system("pause");
	return 0;
}