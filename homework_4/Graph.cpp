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

    int total = 0;//MST的总权值
    vector<int> parent(vertexNum + 1, -1); // parent[i]表示第i个顶点的父节点
    vector<int> key(vertexNum + 1, INT_MAX); // key[i]表示从MST到i的最小权值
    vector<bool> inMST(vertexNum + 1, false); // inMST[i]表示顶点i是否包含在MST中

    // 优先队列存储 (权值, 顶点) 对
    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;

    int start = 1; // 从顶点1开始
    pq.push(make_pair(0, start));
    key[start] = 0;

    while (!pq.empty()) {
		int u = pq.top().second;//权值最小的顶点编号
		pq.pop();//出队

		if (inMST[u]) continue;//如果已经在MST中，跳过

		inMST[u] = true;//标记顶点u已经在MST中
		total += key[u]; // 更新MST的总权值

        // 遍历邻接矩阵
        for (int i = 0; i < weight[u].size(); i++) {
			int v = i; // 顶点u的邻接顶点
			int w = weight[u][i];//顶点u到顶点v的权值
			if (w == 0) continue; // 如果顶点u到顶点v没有边，跳过

			// 如果顶点v不在MST中且顶点u到顶点v的权值小于key[v]
            if (!inMST[v] && w < key[v]) {
				key[v] = w; // 更新key[v]
				pq.push(make_pair(key[v], v)); // 将顶点v加入优先队列
				parent[v] = u; // 更新顶点v的父节点
            }
        }
    }
    // 输出MST的边和总权值
    for (int i = 1; i <= vertexNum; ++i) {
        if (parent[i] != -1) {
            cout << "最小耗费是:" << parent[i] << "和" << i << endl;
        }
    }
    cout << "最小生成树的总权值为:" << total << endl;
}
