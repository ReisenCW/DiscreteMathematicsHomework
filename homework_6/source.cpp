#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <regex>

using namespace std;

// WarShall�㷨
static vector<vector<int>> WarShall(const vector<vector<int>>& matrix)
{
    vector<vector<int>> result(matrix);
    for (int i = 0; i < result.size(); i++) { // �б���
        for (int j = 0; j < result.size(); j++) { // �б���
            // �����j������һ�в�Ϊ0,�򽫵�i��������Ԫ�ؼӵ���j��(�߼���)
            if (result[j][i] != 0) {
                for (int k = 0; k < result.size(); k++) {
                    result[j][k] = result[j][k] | result[i][k]; // ʹ�ð�λ�����
                }
            }
        }
    }
    return result;
}

// �ж�����Ķ�Ԫ��ϵ��ʽ�Ƿ���ȷ
static bool IsRelation(const string& r, int n) {
    string pattern = "(\\s*<\\s*[a-zA-Z0-9]+\\s*,\\s*[a-zA-Z0-9]+\\s*>\\s*,\\s*){" + to_string(n-1) + "}" + "\\s*<\\s*[a-zA-Z0-9]+\\s*,\\s*[a-zA-Z0-9]+\\s*>\\s*";
    return regex_match(r, regex(pattern));
}

// �Ӹ�ʽ����Ķ�Ԫ��ϵ(����<a,b>,<c,d>,<e,f>)����ȡԪ��,���� (a,b), (c,d), (e,f)...
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

// �Ӽ���A�Ͷ�Ԫ��ϵ����ȡ��ϵ����
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
    cout << "�����뼯��A�е�Ԫ�ظ���(������),���س���������һ��: ";
    double elementCnt = 0;
    while (1) {
        cin >> elementCnt;
        // ������
        if (!cin.good() || elementCnt <= 0 || floor(elementCnt) != elementCnt) {
            cout << "�������,����������: ";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    int num = static_cast<int>(elementCnt);
    cout << "���������뼯��A�е�" << num << "��Ԫ��(����:abcd ...... �����ĸ�ʽ),���س���������һ��:" << endl;
    vector<string> setA;
    // ���뼯��A�е�Ԫ��
    for (int i = 1; i <= num; i++) {
        string temp;
        while (1) {
            cout << "�������" << i << "��Ԫ��: ";
            cin >> temp;
            // �����Ԫ���Ѿ�����,����������
            if (find(setA.begin(), setA.end(), temp) != setA.end()) {
                cout << "��Ԫ���Ѿ�����,����������:" << endl;
            }
            else {
                break;
            }
        }
        // ��Ԫ�ؼ��뼯��A
        setA.push_back(temp);
    }
    cout << "�������Ԫ��ϵR�е�Ԫ�ظ���(������),���س���������һ��: ";
    double relationsNum = 0;
    while (1) {
        cin >> relationsNum;
        // ������
        if (!cin.good() || relationsNum <= 0 || floor(relationsNum) != relationsNum) {
            cout << "�������,����������: ";
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
        cout << "����������R�е�" << num2 << "��Ԫ��,��ʽΪ<a,b>,<c,d>,<e,f>(<>��,ǰ���пո�Ӱ��) : " << endl;
        // �����Ԫ��ϵ    
        getline(cin, relation);
        // �ж������ʽ�Ƿ���ȷ
        if (!IsRelation(relation, num2)) {
            cout << "�������,����������: " << endl;
            continue;
        }
        // ��ȡԪ��
        vector<pair<string, string>> relationElements = SubstractRelation(relation);
        // �ж�Ԫ���Ƿ��ڼ���A��
        bool flag = true;
        for (int i = 0; i < relationElements.size(); i++) {
            if (!ElementExist(setA, relationElements[i].first) || !ElementExist(setA, relationElements[i].second)) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            cout << "����Ĺ�ϵ���в����ڵ�Ԫ��,����������: ";
            continue;
        }
        // ��ȡ��ϵ����
        vector<vector<int>> matrix = GetRelationMatrix(setA, relationElements);
        // WarShall�㷨�õ����ݱհ�
        vector<vector<int>> result = WarShall(matrix);
        // ������ݱհ�
        cout << "R�Ĵ��ݱհ�(������ʽ)Ϊ: " << endl;
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