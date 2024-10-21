#include "functions.h"

#define DEBUG 0
#define DEBUG_2 0

bool checkLeagal(const string& str) //�ж�str�ĸ����ַ��Ƿ�����ĸ,�ո�������
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

void deleteSpace(string& str) //ɾ��str�еĿո�
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

int setVar(const string& str, std::set<char>& s) {//��ȡformula�еı�������
	int cnt = 0;
	for (int i = 0; i < str.size(); i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
			cnt++;
			s.insert(str[i]);
		}
	}
	return cnt;
}

char subCaculate(string& subFormula) //���������Ź�ʽ,���ع�ʽ��ֵ
{
	string newStr;
	//�ȴ���������
	int flag = 0;
	for(int i = 0;i < subFormula.size(); i++) {
		while (subFormula[i] == '!') {
			flag++;
			i++;
		}
		
		if (flag % 2) {
			newStr.push_back(!(subFormula[i]-'0')+'0');//��ת��Ϊ����,��ȡ������,��ת��Ϊ�ַ�push��ȥ
			flag = 0;
		}
		else {
			newStr.push_back(subFormula[i]);
		}
	}
	subFormula = newStr;
	newStr.clear();
#if DEBUG
	cout << "ȡ��: "  << subFormula << " ";
#endif
	//�ٴ����������
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
	cout << "ȡ��: " << subFormula << " ";
#endif
	//�ٴ���������
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
	cout << "ȡ��: " << subFormula << " ";
#endif
	//�ٴ����̺������
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
	cout << "�̺�: " << subFormula << " ��: ";
#endif
	//������ֵ�����
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

int formulaCalculate(const string& formula) //���㹫ʽ��ֵ
{
	string Formula = formula;
	std::stack<int> parenthesisStack;
	for (int i = 0; i < Formula.size(); i++) {//��������,����ջ��˼��
		if (Formula[i] == '(') {
			parenthesisStack.push(i);
		}
		else if (Formula[i] == ')') {
			int length = i - parenthesisStack.top() - 1;
			string subFormula = Formula.substr(parenthesisStack.top()+1, length);//��ȡ��ǰ���ڲ������ڵ��ӹ�ʽ
#if DEBUG_2
			cout << " �ӹ�ʽ: " << subFormula << " ";			
#endif
			char ch = subCaculate(subFormula);//�����ӹ�ʽ��ֵ
#if DEBUG_2
			cout << " �ӹ�ʽֵ: " << ch << " ";
#endif
			Formula = Formula.substr(0, parenthesisStack.top()) + ch + Formula.substr(i + 1, Formula.size() - i - 1);//���ӹ�ʽ��ֵ�滻��ԭ��ʽ��
			i = parenthesisStack.top() - 1; // �ƶ�i����һ�������ŵ�λ��
			parenthesisStack.pop();
#if DEBUG_2
			cout << " ȥ����: " << Formula << " ";
#endif
		}
	}
	return subCaculate(Formula) - '0';
}

void printResult(const string& formula, const std::set<char>& varSet) //�����ֵ��
{
	//�����ֵ��ĵ�һ��(������)
	cout << endl;
	cout << "�����ֵ������:" << endl;
	for (auto i : varSet) {
		cout << i << "\t";
	}
	cout << formula << endl;
	//�����ֵ���������(��������ȡֵ)
	int nowValue = 0;//ʮ������,ÿ��һ�м�1,����������Ʊ�ʾ��������ȡֵ
	int formulaResult = 0;//��ʽ��ֵ
	int* m = new int[(size_t)pow(2, varSet.size())];//�洢����ʽ�Ľ��,����������ʽ
	for (int i = 0; i < pow(2,varSet.size()); i++,nowValue++) {
		int temp[26] = {0};//�±��ӦӢ����ĸ,ֵ��Ӧ��ȡֵ
        string bits;//����ʽ�еı�����Ϊ��ֵ��������ַ��洢��bits��
		int* varValue = new int[varSet.size()];//�洢��������ȡֵ
        for (int j = (int)varSet.size() - 1; j >= 0; j--) {
			varValue[j] = ((nowValue & (1 << j)) >> j);
			cout << varValue[j] << "\t";//�����������ȡֵ
			//��ȡ��nλ��ֵ��������1 << n������&�����,����nowValue�Ķ�������ֻ��1<<n�Ķ�������1��Ӧ��λ�ᱻ����������λ���ᱻ��Ϊ0
		}
		int k = (int)varSet.size() - 1;
		for(auto it = varSet.begin();it != varSet.end() && k >= 0;it++,k--) {
			temp[*it - 'a'] = varValue[k];
		}
		for (int j = 0; j < formula.size(); j++) //����ʽ�еı�����Ϊ�����ַ�,�������
		{
			if (formula[j] >= 'a' && formula[j] <= 'z') {
				bits.push_back(temp[formula[j] - 'a'] + '0');//�Ǳ����ͽ��丳ֵ���ֵ����bits
			}
			else {
				bits.push_back(formula[j]);//���Ǳ���˵���������,��ֱ�Ӵ���bits
			}
		}
#if DEBUG
		cout << " bits: " << bits << " ";
#endif
		formulaResult = formulaCalculate(bits);//���㹫ʽ��ֵ
		cout << formulaResult << endl;
		m[i] = formulaResult;//�洢��ʽ��ֵ
		delete[] varValue;
	}
	cout << endl;
	//����ʽ
	//����ȡ��ʽ
	bool first = true;//�ж��Ƿ��ǵ�һ����
	cout << "����ȡ��ʽΪ: " << endl;
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
	//����ȡ��ʽ
	first = true;
	cout << "����ȡ��ʽΪ: " << endl;
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