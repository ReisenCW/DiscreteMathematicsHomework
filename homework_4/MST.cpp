#include <iostream>
#include "Graph.h"

int main()
{
	using namespace std;
	int vertexNum, edgeNum;
	cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):";
	cin >> vertexNum >> edgeNum;
	Graph g(vertexNum, edgeNum);
	cout << "请输入两条边的节点序号以及它们的权值(以空格分隔各个数):" << endl;
	while (edgeNum--) {
		int from, to, weight;
		cin >> from >> to >> weight;
		g.AddEdge(from, to, weight);
	}
	g.PrintMST();
	return 0;
}
