#include <iostream>
#include <string>
#include "AdjGraph.h"
#include "Functions.h"

int main() {
    int n = 3; // �����Ӵ�����
	const char* alphabet = "01"; // ��ĸ��
    std::cout << "DeBruijn����: " << DeBruijn(n, alphabet) << std::endl;
    return 0;
}