#pragma once
#include <iostream>
#include <vector>
class Graph {
private:
	std::vector<std::vector<int>> weight;//����->�յ� = Ȩֵ
	int vertexNum;
	int edgeNum;
public:
	Graph() {};
	Graph(int vertexNum, int edgeNum);
	void AddEdge(int from, int to, int weight);
	void PrintMST();
};