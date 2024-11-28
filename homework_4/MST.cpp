#include <iostream>
#include "Graph.h"

int main()
{
	using namespace std;
	int vertexNum, edgeNum;
	cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ(�Կո�ָ�����������������0����):";
	cin >> vertexNum >> edgeNum;
	Graph g(vertexNum, edgeNum);
	cout << "�����������ߵĽڵ�����Լ����ǵ�Ȩֵ(�Կո�ָ�������):" << endl;
	while (edgeNum--) {
		int from, to, weight;
		cin >> from >> to >> weight;
		g.AddEdge(from, to, weight);
	}
	g.PrintMST();
	return 0;
}
