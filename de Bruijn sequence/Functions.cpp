#include "Functions.h"

#define _DEBUG_ 1

std::vector<std::string> GenerateVertices(int n, const std::string& alphabet) //����DeBruijnͼ�Ķ��㴮����
{
	int alphabetLen = (int)alphabet.length();
	int vertexNum = (int)pow(alphabetLen, n - 1);//������Ϊ��ĸ���ȵ�n-1�η�
	int vertexStrLen = n - 1;//���㴮����Ϊ�Ӵ����ȼ�1
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
			std::string newVertexStr = vertexStr + c;//�ߵ��ַ���Ϊ���㴮�ֱ������ĸ���и����ַ�,���бߵ��ַ�����������ĸ����Ϊn�����������Ӵ�
			int to = graph.GetIndex(newVertexStr.substr(1, newVertexStr.size()));//���ӵ��Ķ����Ӧ���ַ���Ϊ���ַ���ȥ�����ַ�
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
	
	for (auto& edge : graph.adjList[v]) //�����ö���ָ������б�
	{
		if (!edgeVisited[v][edge.to]) {//����ñ�û�з��ʹ�
			edgeVisited[v][edge.to] = true;//��Ǹñ߷��ʹ�
			EulerCircuitDFS(graph, edge.to, circuit, edgeVisited);//�ݹ���ʸñ����ӵĶ���
		}
	}
	circuit.push_back(v);
}

//ʹ��Hierholzer�㷨Ѱ��ŷ����·
std::vector<int> FindEulerianCircuit(AdjGraph& graph)
{
	std::vector<int> circuit;
	std::vector<std::vector<int>> edgeVisited(graph.GetVertexNum(), std::vector<int>(graph.GetVertexNum(), 0));//��¼���Ƿ���ʹ�
	EulerCircuitDFS(graph, 1, circuit, edgeVisited);//�����һ�����㿪ʼDFS,����ѡ�񶥵�1
#if _DEBUG_
	std::cout << "Eulerian Circuit-";
	for (int i : circuit) {
		std::cout << "-" << graph.GetVertexStr(i);
	}
	std::cout << std::endl;
#endif
	std::reverse(circuit.begin(), circuit.end());//��ΪHierholzer�㷨�õ����������ŷ����·,������Ҫ��ת
	return circuit;
}

std::string DeBruijn(int n, const std::string& alphabet) {
	std::vector<std::string> vertices = GenerateVertices(n, alphabet);//��ö��㴮����
	AdjGraph graph(vertices);
	GenerateDeBruijnGraph(graph, alphabet);//����DeBruijnͼ
	std::vector<int> circuit = FindEulerianCircuit(graph);//Ѱ��ŷ����·
	std::string deBruijnStr;
	for (int i = 0; i < circuit.size() - 1; i++) {
		deBruijnStr += graph.GetVertexStr(circuit[i])[0];
	}
	deBruijnStr += graph.GetVertexStr(circuit[0]);
	return deBruijnStr;
}