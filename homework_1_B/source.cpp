#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <chrono>
#include "functions.h"
#include <set>

int main() {
	//只判断了英文状态下的运算符
	using std::cout;
	using std::cin;
	using std::endl;
	using std::string;
	string formula;
	std::set<char> varSet;
	printf("***************************************\n");  //标语
	printf("**                                   **\n");
	printf("**         欢迎进入逻辑运算软件      **\n");
	printf("**   (可运算真值表,主范式,支持括号)  **\n");
	printf("**                                   **\n");
	printf("**              用!表示非            **\n");
	printf("**              用&表示与            **\n");
	printf("**              用|表示或            **\n");
	printf("**             用^表示蕴含           **\n");
	printf("**             用~表示等值           **\n");
	printf("**                                   **\n");
	printf("***************************************\n\n");
	printf("请输入一个合法的命题公式:\n");  //输入式子
	getline(cin, formula);
	while(!checkLeagal(formula)) {//判断输入是否合法
		printf("输入错误,请重新输入:\n");
		std::this_thread::sleep_for(std::chrono::seconds(2));//休息2s
		printf("请输入一个合法的命题公式:\n");
		getline(cin, formula);
	}
	//去除空格
	deleteSpace(formula);
	
	//输出变量个数,并把变量存入set中
	cout << endl;
	printf("该式子中的变量个数为: %d\n", setVar(formula, varSet));

	//输出结果
	printResult(formula, varSet);


	system("pause");
	return 0;
}