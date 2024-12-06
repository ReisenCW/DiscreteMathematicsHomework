#pragma once
#include <iostream>
#include <string>
#include "AdjGraph.h"

std::vector<std::string> GenerateVertices(int n, const std::string& alphabet); //生成DeBruijn图的顶点串集合
void GenerateDeBruijnGraph(AdjGraph& graph, const std::string& alphabet);//生成DeBruijn图
std::vector<int> FindEulerianCircuit(AdjGraph& graph);//寻找欧拉回路
void EulerCircuitDFS(AdjGraph& graph, int v, std::vector<int>& circuit, std::vector<std::vector<int>>& edgeVisited);//DFS寻找欧拉回路
std::string DeBruijn(int n, const std::string& alphabet);//生成DeBruijn序列
