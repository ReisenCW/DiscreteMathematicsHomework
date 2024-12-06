#pragma once
#include <iostream>
#include <string>
#include "AdjGraph.h"

std::vector<std::string> GenerateVertices(int n, const std::string& alphabet); //����DeBruijnͼ�Ķ��㴮����
void GenerateDeBruijnGraph(AdjGraph& graph, const std::string& alphabet);//����DeBruijnͼ
std::vector<int> FindEulerianCircuit(AdjGraph& graph);//Ѱ��ŷ����·
void EulerCircuitDFS(AdjGraph& graph, int v, std::vector<int>& circuit, std::vector<std::vector<int>>& edgeVisited);//DFSѰ��ŷ����·
std::string DeBruijn(int n, const std::string& alphabet);//����DeBruijn����
