#include "Graph.h"

Graph::Graph(const std::vector<std::vector<size_t>>& adjList)
	: m_adjList(adjList)
	, m_size(adjList.size())
{
	m_pairU.resize(m_adjList.size());
	m_pairV.resize(m_adjList.size());
	m_distance.resize(m_adjList.size());
}

void Graph::AddFreeVertices(std::queue<size_t>& queue)
{
	for (size_t u = 1; u < m_size; u++)
	{
		if (m_pairU[u] == 0)
		{
			m_distance[u] = 0;
			queue.push(u);
			continue;
		}
		m_distance[u] = SIZE_MAX;
	}
}

bool Graph::Bfs()
{
	std::queue<size_t> queue;
	AddFreeVertices(queue); // добавляем в очередь свободные вершины, инициализируем distance

	m_distance[0] = SIZE_MAX; // помечаем фиктивную нулевую вершину

	while (!queue.empty())
	{
		size_t u = queue.front();
		queue.pop();

		if (m_distance[u] < m_distance[0])
		// отсечение путей длиннее кратчайшего (если m_distance[0] != SIZE_MAX то путь уже найден, ищем те что не превышают его длину)
		{
			for (auto v : m_adjList[u])
			{
				size_t nextU = m_pairV[v];
				if (m_distance[nextU] == SIZE_MAX) // если nextU == 0 (фиктивная) или вершина u имеет пару
				{
					m_distance[nextU] = m_distance[u] + 1;
					queue.push(nextU);
				}
			}
		}
	}

	return m_distance[0] != SIZE_MAX;
}

bool Graph::Dfs(size_t u)
{
	if (u == 0)
	{
		return true;
	}

	for (auto v : m_adjList[u])
	{
		size_t nextU = m_pairV[v];
		if (m_distance[nextU] == m_distance[u] + 1 && Dfs(nextU))
		{
			m_pairV[v] = u;
			m_pairU[u] = v;

			return true;
		}
	}

	m_distance[u] = SIZE_MAX;
	return false;
}

void Graph::FindMaxMatch()
{
	while (Bfs())
	{
		for (size_t u = 1; u < m_size; u++)
		{
			if (m_pairU[u] == 0)
			{
				Dfs(u);
			}
		}
	}
}

void Graph::PrintMatches() const
{
	for (size_t u = 1; u < m_size; ++u)
	{
		if (m_pairU[u] != 0)
		{
			std::cout << u << " -> " << m_pairU[u] << "\n";
		}
	}
}
