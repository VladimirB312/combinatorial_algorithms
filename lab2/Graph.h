#pragma once
#include <istream>
#include <map>
#include <vector>

using AdjacencyMatrix = std::vector<std::vector<size_t>>;
using AdjacencyList = std::vector<std::vector<size_t>>;
using Components = std::map<size_t, std::vector<size_t>>;

class Graph {
public:
	Graph(const AdjacencyList& list);
	Components GetComponents();
private:
	AdjacencyMatrix m_adjacencyMatrix{};
	AdjacencyList m_adjacencyList{};
	AdjacencyList m_invertedList{};
	Components m_components{};
	std::vector<bool> m_visited{};
	std::vector<size_t> m_timeIn{};
	std::vector<size_t> m_timeOut{};
	std::vector<std::pair<size_t, size_t>> m_sortedTime;
	AdjacencyList GetAdjacencyListFromAdjacencyMatrix(const AdjacencyMatrix& matrix);
	AdjacencyMatrix GetAdjacencyMatrixFromAdjacencyList(const AdjacencyList& adjList);
	void Dfs(size_t vertex, size_t& time);
	void SetTimeStamps();
	void SetInvertedList();
	void DfsOnInvertedGraph(size_t vertex, size_t componentNumber);
	void TimeSort();
	void MarksComponents();
};