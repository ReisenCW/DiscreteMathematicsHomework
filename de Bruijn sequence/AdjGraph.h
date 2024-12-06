#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

struct Edge {
	int to;
	std::string edgeStr;
};

class AdjGraph {
public:
	AdjGraph(const std::vector<std::string>& data);
	void AddEdge(int from, int to, const std::string& edgeStr);
	void PrintGraph();
	int GetVertexNum() const { return vertexNum; }
	int GetIndex(const std::string& str) { return stringToIndex[str]; }
	std::string GetVertexStr(int index) { return indexToString[index]; }
	std::vector<std::vector<Edge>> adjList;
private:
	int vertexNum;
	std::unordered_map<std::string, int> stringToIndex;
	std::vector<std::string> indexToString;
};