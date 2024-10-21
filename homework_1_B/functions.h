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

bool checkLeagal(const std::string& str); //判断str的各个字符是否是字母,空格或运算符

void deleteSpace(std::string& str); //删除str中的空格

int setVar(const std::string& formula,std::set<char>& set); //获取formula中的变量个数

char subCaculate(std::string& subFormula);

int formulaCalculate(const std::string& formula); //计算公式的值

void printResult(const std::string& formula, const std::set<char>& varSet); //输出真值表