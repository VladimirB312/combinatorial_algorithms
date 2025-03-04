#pragma once
#include <istream>
#include <map>
#include <vector>

using AdjacencyMatrix = std::vector<std::vector<size_t>>;
using AdjacencyList = std::map<size_t, std::vector<size_t>>;

struct TimeStamp {
	size_t in = 0;
	size_t out = 0;
};

class Graph {
public:
	Graph(const AdjacencyMatrix& matrix);
	void PrintTimeStamps(std::ostream& output);
	void SetTimeStamps();
private:
	AdjacencyMatrix adjacencyMatrix{};
	AdjacencyList adjacencyList{};
	size_t dimension;
	std::vector<bool> visited{};
	std::map<size_t, TimeStamp> timeStamps{};
	void DfsMatrix(size_t vertex, size_t& time);
	size_t GetMaxVertexNumber();
	AdjacencyList GetAdjacencyListFromAdjacencyMatrix();
	AdjacencyMatrix GetAdjacencyMatrixFromAdjacencyList();
};