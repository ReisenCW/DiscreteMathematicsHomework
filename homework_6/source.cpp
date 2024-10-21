#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <regex>

using namespace std;

// WarShall算法
static vector<vector<int>> WarShall(const vector<vector<int>>& matrix)
{
    vector<vector<int>> result(matrix);
    for (int i = 0; i < result.size(); i++) { // 列遍历
        for (int j = 0; j < result.size(); j++) { // 行遍历
            // 如果第j列中有一行不为0,则将第i行中所有元素加到第j行(逻辑加)
            if (result[j][i] != 0) {
                for (int k = 0; k < result.size(); k++) {
                    result[j][k] = result[j][k] | result[i][k]; // 使用按位运算符
                }
            }
        }
    }
    return result;
}

// 判断输入的二元关系格式是否正确
static bool IsRelation(const string& r, int n) {
    string pattern = "(\\s*<\\s*[a-zA-Z0-9]+\\s*,\\s*[a-zA-Z0-9]+\\s*>\\s*,\\s*){" + to_string(n-1) + "}" + "\\s*<\\s*[a-zA-Z0-9]+\\s*,\\s*[a-zA-Z0-9]+\\s*>\\s*";
    return regex_match(r, regex(pattern));
}

// 从格式输入的二元关系(形如<a,b>,<c,d>,<e,f>)中提取元素,返回 (a,b), (c,d), (e,f)...
static vector<pair<string, string>> SubstractRelation(const string& r) {
    vector<pair<string, string>> result;
    regex pattern("<\\s*([a-zA-Z0-9]+)\\s*,\\s*([a-zA-Z0-9]+)\\s*>");
    sregex_iterator it(r.begin(), r.end(), pattern);
    sregex_iterator end;
    while (it != end) {
        result.push_back(make_pair(it->str(1), it->str(2)));
        it++;
    }
    return result;
}

static bool ElementExist(const vector<string>& setA, const string& element) {
    return find(setA.begin(), setA.end(), element) != setA.end();
}

// 从集合A和二元关系中提取关系矩阵
static vector<vector<int>> GetRelationMatrix(const vector<string>& setA, const vector<pair<string, string>>& relation) {
    vector<vector<int>> matrix(setA.size(), vector<int>(setA.size(), 0));
    for (int i = 0; i < relation.size(); i++) {
        size_t index1 = find(setA.begin(), setA.end(), relation[i].first) - setA.begin();
        size_t index2 = find(setA.begin(), setA.end(), relation[i].second) - setA.begin();
        matrix[index1][index2] = 1;
    }
    return matrix;
}

static void menu() {
    cout << "请输入集合A中的元素个数(正整数),按回车键输入下一项: ";
    double elementCnt = 0;
    while (1) {
        cin >> elementCnt;
        // 错误处理
        if (!cin.good() || elementCnt <= 0 || floor(elementCnt) != elementCnt) {
            cout << "输入错误,请重新输入: ";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    int num = static_cast<int>(elementCnt);
    cout << "请依次输入集合A中的" << num << "个元素(形如:abcd ...... 这样的格式),按回车键输入下一项:" << endl;
    vector<string> setA;
    // 输入集合A中的元素
    for (int i = 1; i <= num; i++) {
        string temp;
        while (1) {
            cout << "请输入第" << i << "个元素: ";
            cin >> temp;
            // 如果该元素已经存在,则重新输入
            if (find(setA.begin(), setA.end(), temp) != setA.end()) {
                cout << "该元素已经存在,请重新输入:" << endl;
            }
            else {
                break;
            }
        }
        // 将元素加入集合A
        setA.push_back(temp);
    }
    cout << "请输入二元关系R中的元素个数(正整数),按回车键输入下一项: ";
    double relationsNum = 0;
    while (1) {
        cin >> relationsNum;
        // 错误处理
        if (!cin.good() || relationsNum <= 0 || floor(relationsNum) != relationsNum) {
            cout << "输入错误,请重新输入: ";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    int num2 = static_cast<int>(relationsNum);
    string relation;
    cin.ignore();
    while (1) {
        cout << "请依次输入R中的" << num2 << "个元素,形式为<a,b>,<c,d>,<e,f>(<>与,前后有空格不影响) : " << endl;
        // 输入二元关系    
        getline(cin, relation);
        // 判断输入格式是否正确
        if (!IsRelation(relation, num2)) {
            cout << "输入错误,请重新输入: " << endl;
            continue;
        }
        // 提取元素
        vector<pair<string, string>> relationElements = SubstractRelation(relation);
        // 判断元素是否在集合A中
        bool flag = true;
        for (int i = 0; i < relationElements.size(); i++) {
            if (!ElementExist(setA, relationElements[i].first) || !ElementExist(setA, relationElements[i].second)) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            cout << "输入的关系中有不存在的元素,请重新输入: ";
            continue;
        }
        // 提取关系矩阵
        vector<vector<int>> matrix = GetRelationMatrix(setA, relationElements);
        // WarShall算法得到传递闭包
        vector<vector<int>> result = WarShall(matrix);
        // 输出传递闭包
        cout << "R的传递闭包(集合形式)为: " << endl;
        cout << "t(R) = {";
        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result.size(); j++) {
                if (result[i][j] == 1) {
                    cout << "<" << setA[i] << "," << setA[j] << ">,";
                }
            }
        }
        cout << "\b}" << endl;
        return;
    }
}

int main() {
    menu();
    return 0;
}
/*
test:
5
a b c d e
6
< a , b > , < b ,    c   >   ,<c,   c>,<c,   d>   ,<e, a>, < e  ,d> 
*/