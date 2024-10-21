#include "functions.h"

#define DEBUG 0
#define DEBUG_2 0

bool checkLeagal(const string& str) //判断str的各个字符是否是字母,空格或运算符
{
	for (int i = 0; i < str.size(); i++) {
		if ((str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z') && str[i] != '!' && str[i] != '&' && str[i] != '|' && str[i] != '^' && str[i] != '~' && str[i] != '(' && str[i] != ')' && str[i] != ' ') {
        #if DEBUG
            cout << "error:" << str[i] << endl;
        #endif
            return false;
		}
	}
	return true;
}

void deleteSpace(string& str) //删除str中的空格
{
    string newStr;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] != ' ') {
			newStr.push_back(str[i]);
		}
	}
    str = newStr;
#if DEBUG
    cout << str << endl;
#endif
}

int setVar(const string& str, std::set<char>& s) {//获取formula中的变量个数
	int cnt = 0;
	for (int i = 0; i < str.size(); i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
			cnt++;
			s.insert(str[i]);
		}
	}
	return cnt;
}

char subCaculate(string& subFormula) //处理无括号公式,返回公式的值
{
	string newStr;
	//先处理非运算符
	int flag = 0;
	for(int i = 0;i < subFormula.size(); i++) {
		while (subFormula[i] == '!') {
			flag++;
			i++;
		}
		
		if (flag % 2) {
			newStr.push_back(!(subFormula[i]-'0')+'0');//先转化为数字,作取反操作,再转化为字符push进去
			flag = 0;
		}
		else {
			newStr.push_back(subFormula[i]);
		}
	}
	subFormula = newStr;
	newStr.clear();
#if DEBUG
	cout << "取非: "  << subFormula << " ";
#endif
	//再处理与运算符
	for (int i = 0; i < subFormula.size(); i++) {
		if (subFormula[i] == '&') {
			int a = newStr.back() - '0';
			int b = subFormula[i + 1] - '0';
			newStr.pop_back();
			newStr.push_back((a & b) + '0');
			i++;
		}
		else {
			newStr.push_back(subFormula[i]);
		}
	}
	subFormula = newStr;
	newStr.clear();
#if DEBUG
	cout << "取与: " << subFormula << " ";
#endif
	//再处理或运算符
	for (int i = 0; i < subFormula.size(); i++) {
		if (subFormula[i] == '|') {
			int a = newStr.back() - '0';
			int b = subFormula[i + 1] - '0';
			newStr.pop_back();
			newStr.push_back((a | b) + '0');
			i++;
		}
		else {
			newStr.push_back(subFormula[i]);
		}
	}
	subFormula = newStr;
	newStr.clear();
#if DEBUG
	cout << "取或: " << subFormula << " ";
#endif
	//再处理蕴含运算符
	for (int i = 0; i < subFormula.size(); i++) {
		if (subFormula[i] == '^') {
			int a = newStr.back() - '0';
			int b = subFormula[i + 1] - '0';
			newStr.pop_back();
			newStr.push_back(((!a) | b) + '0');
			i++;
		}
		else {
			newStr.push_back(subFormula[i]);
		}
	}
	subFormula = newStr;
	newStr.clear();
#if DEBUG
	cout << "蕴含: " << subFormula << " 答案: ";
#endif
	//最后处理等值运算符
	for (int i = 0; i < subFormula.size(); i++) {
		if (subFormula[i] == '~') {
			int a = newStr.back() - '0';
			int b = subFormula[i + 1] - '0';
			newStr.pop_back();
			newStr.push_back(((a & b) | ((!a) & (!b))) + '0');
			i++;
		}
		else {
			newStr.push_back(subFormula[i]);
		}
	}
	return newStr[0];
}

int formulaCalculate(const string& formula) //计算公式的值
{
	string Formula = formula;
	std::stack<int> parenthesisStack;
	for (int i = 0; i < Formula.size(); i++) {//处理括号,利用栈的思想
		if (Formula[i] == '(') {
			parenthesisStack.push(i);
		}
		else if (Formula[i] == ')') {
			int length = i - parenthesisStack.top() - 1;
			string subFormula = Formula.substr(parenthesisStack.top()+1, length);//获取当前最内层括号内的子公式
#if DEBUG_2
			cout << " 子公式: " << subFormula << " ";			
#endif
			char ch = subCaculate(subFormula);//计算子公式的值
#if DEBUG_2
			cout << " 子公式值: " << ch << " ";
#endif
			Formula = Formula.substr(0, parenthesisStack.top()) + ch + Formula.substr(i + 1, Formula.size() - i - 1);//将子公式的值替换到原公式中
			i = parenthesisStack.top() - 1; // 移动i到上一个左括号的位置
			parenthesisStack.pop();
#if DEBUG_2
			cout << " 去括号: " << Formula << " ";
#endif
		}
	}
	return subCaculate(Formula) - '0';
}

void printResult(const string& formula, const std::set<char>& varSet) //输出真值表
{
	//输出真值表的第一行(各变量)
	cout << endl;
	cout << "输出真值表如下:" << endl;
	for (auto i : varSet) {
		cout << i << "\t";
	}
	cout << formula << endl;
	//输出真值表的其余行(各变量的取值)
	int nowValue = 0;//十进制数,每换一行加1,利用其二进制表示各变量的取值
	int formulaResult = 0;//公式的值
	int* m = new int[(size_t)pow(2, varSet.size())];//存储各公式的结果,用于求主范式
	for (int i = 0; i < pow(2,varSet.size()); i++,nowValue++) {
		int temp[26] = {0};//下标对应英文字母,值对应其取值
        string bits;//将公式中的变量变为赋值后的数字字符存储在bits中
		int* varValue = new int[varSet.size()];//存储各变量的取值
        for (int j = (int)varSet.size() - 1; j >= 0; j--) {
			varValue[j] = ((nowValue & (1 << j)) >> j);
			cout << varValue[j] << "\t";//输出各变量的取值
			//获取第n位的值，可以用1 << n，再用&运算符,这样nowValue的二进制中只有1<<n的二进制中1对应的位会被保留，其他位都会被置为0
		}
		int k = (int)varSet.size() - 1;
		for(auto it = varSet.begin();it != varSet.end() && k >= 0;it++,k--) {
			temp[*it - 'a'] = varValue[k];
		}
		for (int j = 0; j < formula.size(); j++) //将公式中的变量变为数字字符,方便计算
		{
			if (formula[j] >= 'a' && formula[j] <= 'z') {
				bits.push_back(temp[formula[j] - 'a'] + '0');//是变量就将其赋值后的值存入bits
			}
			else {
				bits.push_back(formula[j]);//不是变量说明是运算符,就直接存入bits
			}
		}
#if DEBUG
		cout << " bits: " << bits << " ";
#endif
		formulaResult = formulaCalculate(bits);//计算公式的值
		cout << formulaResult << endl;
		m[i] = formulaResult;//存储公式的值
		delete[] varValue;
	}
	cout << endl;
	//主范式
	//主析取范式
	bool first = true;//判断是否是第一个项
	cout << "主析取范式为: " << endl;
	for(int i = 0;i < pow(2,varSet.size());i++) {
		if (m[i] == 1) {
			if (first) {
				first = false;
				cout << "m<" << i << ">";
			}
			else {
				cout << "\\/ m<" << i << ">";
			}
			cout << " ";
		}
	}
	if (first) {
		cout << "1";
	}
	cout << endl;
	//主合取范式
	first = true;
	cout << "主合取范式为: " << endl;
	for(int i = 0;i < pow(2,varSet.size());i++) {
		if (m[i] == 0) {
			if (first) {
				first = false;
				cout << "M<" << i << ">";
			}
			else {
				cout << "/\\ M<" << i << ">";
			}
			cout << " ";
		}	
	}
	if (first) {
		cout << "0";
	}
	cout << endl;
}