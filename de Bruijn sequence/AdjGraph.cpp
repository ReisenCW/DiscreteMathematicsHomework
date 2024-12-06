#include "AdjGraph.h"

AdjGraph::AdjGraph(const std::vector<std::string>& data) : vertexNum((int)data.size()), indexToString(data)
{
	adjList.resize(vertexNum);
	for (int i = 0; i < vertexNum; i++) {
		stringToIndex[data[i]] = i;
	}
}

void AdjGraph::AddEdge(int from, int to, const std::string& edgeStr)
{
	adjList[from].push_back({ to, edgeStr });
}

void AdjGraph::PrintGraph()
{
	for (int i = 0; i < vertexNum; i++) {
		
		for (auto& j : adjList[i]) {
			std::cout << GetVertexStr(i) << "！！>";
			std::cout << j.edgeStr << "！！>" << GetVertexStr(j.to) << "   ";
		}
		std::cout << std::endl;
	}
}
