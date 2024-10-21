#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;

bool checkLeagal(const std::string& str); //�ж�str�ĸ����ַ��Ƿ�����ĸ,�ո�������

void deleteSpace(std::string& str); //ɾ��str�еĿո�

int setVar(const std::string& formula,std::set<char>& set); //��ȡformula�еı�������

char subCaculate(std::string& subFormula);

int formulaCalculate(const std::string& formula); //���㹫ʽ��ֵ

void printResult(const std::string& formula, const std::set<char>& varSet); //�����ֵ��