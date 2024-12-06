#include <iostream>
#include <string>
#include "AdjGraph.h"
#include "Functions.h"

int main() {
    int n = 3; // 序列子串长度
	const char* alphabet = "01"; // 字母表
    std::cout << "DeBruijn序列: " << DeBruijn(n, alphabet) << std::endl;
    return 0;
}