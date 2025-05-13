#pragma once
#pragma once
#include <iostream>
#include <queue>
#include <vector>

class Graph
{
public:
	explicit Graph(const std::vector<std::vector<size_t>>& adjList);

	void AddFreeVertices(std::queue<size_t>& queue);

	bool Bfs();

	bool Dfs(size_t u);

	void FindMaxMatch();

	void PrintMatches() const;

private:
	size_t m_size;
	std::vector<size_t> m_distance;
	std::vector<size_t> m_pairU;
	std::vector<size_t> m_pairV;
	std::vector<std::vector<size_t>> m_adjList;
};
