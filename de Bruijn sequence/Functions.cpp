#include "Functions.h"

#define _DEBUG_ 1

std::vector<std::string> GenerateVertices(int n, const std::string& alphabet) //生成DeBruijn图的顶点串集合
{
	int alphabetLen = (int)alphabet.length();
	int vertexNum = (int)pow(alphabetLen, n - 1);//顶点数为字母表长度的n-1次方
	int vertexStrLen = n - 1;//顶点串长度为子串长度减1
	std::vector<std::string> vertices;
	for (int i = 0; i < vertexNum; i++) {
		std::string vertexStr;
		int temp = i;
		for (int j = 0; j < vertexStrLen; j++) {
			vertexStr = alphabet[temp % alphabetLen] + vertexStr;
			temp /= alphabetLen;
		}
		vertices.push_back(vertexStr);
	}

#if _DEBUG_
	std::cout << "Vertices: ";
	for (std::string str : vertices) {
		std::cout << str << " ";
	}
	std::cout << std::endl;
# endif

	return vertices;
}

void GenerateDeBruijnGraph(AdjGraph& graph, const std::string& alphabet) {
	int vertexNum = graph.GetVertexNum();
	for (int i = 0; i < vertexNum; i++) {
		std::string vertexStr = graph.GetVertexStr(i);
		for (char c : alphabet) {
			std::string newVertexStr = vertexStr + c;//边的字符串为顶点串分别加上字母表中各个字符,所有边的字符串构成了字母表长度为n的所有序列子串
			int to = graph.GetIndex(newVertexStr.substr(1, newVertexStr.size()));//连接到的顶点对应的字符串为边字符串去掉首字符
			graph.AddEdge(i, to, newVertexStr);
		}
	}
#if _DEBUG_
	std::cout << std::endl << "DeBruijn Graph: " << std::endl;
	graph.PrintGraph();
	std::cout << std::endl;
#endif
}

void EulerCircuitDFS(AdjGraph& graph, int v, std::vector<int>& circuit, std::vector<std::vector<int>>& edgeVisited) {
	
	for (auto& edge : graph.adjList[v]) //遍历该顶点指向的所有边
	{
		if (!edgeVisited[v][edge.to]) {//如果该边没有访问过
			edgeVisited[v][edge.to] = true;//标记该边访问过
			EulerCircuitDFS(graph, edge.to, circuit, edgeVisited);//递归访问该边连接的顶点
		}
	}
	circuit.push_back(v);
}

//使用Hierholzer算法寻找欧拉回路
std::vector<int> FindEulerianCircuit(AdjGraph& graph)
{
	std::vector<int> circuit;
	std::vector<std::vector<int>> edgeVisited(graph.GetVertexNum(), std::vector<int>(graph.GetVertexNum(), 0));//记录边是否访问过
	EulerCircuitDFS(graph, 1, circuit, edgeVisited);//随便找一个顶点开始DFS,这里选择顶点1
#if _DEBUG_
	std::cout << "Eulerian Circuit-";
	for (int i : circuit) {
		std::cout << "-" << graph.GetVertexStr(i);
	}
	std::cout << std::endl;
#endif
	std::reverse(circuit.begin(), circuit.end());//因为Hierholzer算法得到的是逆序的欧拉回路,所以需要反转
	return circuit;
}

std::string DeBruijn(int n, const std::string& alphabet) {
	std::vector<std::string> vertices = GenerateVertices(n, alphabet);//获得顶点串集合
	AdjGraph graph(vertices);
	GenerateDeBruijnGraph(graph, alphabet);//生成DeBruijn图
	std::vector<int> circuit = FindEulerianCircuit(graph);//寻找欧拉回路
	std::string deBruijnStr;
	for (int i = 0; i < circuit.size() - 1; i++) {
		deBruijnStr += graph.GetVertexStr(circuit[i])[0];
	}
	deBruijnStr += graph.GetVertexStr(circuit[0]);
	return deBruijnStr;
}