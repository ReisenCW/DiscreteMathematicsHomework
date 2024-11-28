#include "Graph.h"
#include <queue>
#include <climits>

Graph::Graph(int vertexNum, int edgeNum) :vertexNum(vertexNum), edgeNum(edgeNum) {
    weight.resize(vertexNum + 1, std::vector<int>(vertexNum + 1, 0));
}

void Graph::AddEdge(int from, int to, int weight) {
    this->weight[from][to] = weight;
    this->weight[to][from] = weight;
}

void Graph::PrintMST() {
    using std::cout;
    using std::endl;
    using std::priority_queue;
    using std::vector;
    using std::pair;
    using std::make_pair;

    int total = 0;//MST����Ȩֵ
    vector<int> parent(vertexNum + 1, -1); // parent[i]��ʾ��i������ĸ��ڵ�
    vector<int> key(vertexNum + 1, INT_MAX); // key[i]��ʾ��MST��i����СȨֵ
    vector<bool> inMST(vertexNum + 1, false); // inMST[i]��ʾ����i�Ƿ������MST��

    // ���ȶ��д洢 (Ȩֵ, ����) ��
    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;

    int start = 1; // �Ӷ���1��ʼ
    pq.push(make_pair(0, start));
    key[start] = 0;

    while (!pq.empty()) {
		int u = pq.top().second;//Ȩֵ��С�Ķ�����
		pq.pop();//����

		if (inMST[u]) continue;//����Ѿ���MST�У�����

		inMST[u] = true;//��Ƕ���u�Ѿ���MST��
		total += key[u]; // ����MST����Ȩֵ

        // �����ڽӾ���
        for (int i = 0; i < weight[u].size(); i++) {
			int v = i; // ����u���ڽӶ���
			int w = weight[u][i];//����u������v��Ȩֵ
			if (w == 0) continue; // �������u������vû�бߣ�����

			// �������v����MST���Ҷ���u������v��ȨֵС��key[v]
            if (!inMST[v] && w < key[v]) {
				key[v] = w; // ����key[v]
				pq.push(make_pair(key[v], v)); // ������v�������ȶ���
				parent[v] = u; // ���¶���v�ĸ��ڵ�
            }
        }
    }
    // ���MST�ıߺ���Ȩֵ
    for (int i = 1; i <= vertexNum; ++i) {
        if (parent[i] != -1) {
            cout << "��С�ķ���:" << parent[i] << "��" << i << endl;
        }
    }
    cout << "��С����������ȨֵΪ:" << total << endl;
}
