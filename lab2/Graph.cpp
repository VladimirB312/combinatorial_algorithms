#include "Graph.h"
#include <sstream>
#include <algorithm>
#include <iostream>

Graph::Graph(const AdjacencyList& list)
	: m_adjacencyList(list)
{
	m_visited.resize(m_adjacencyList.size(), false);
	m_timeIn.resize(m_adjacencyList.size(), 0);
	m_timeOut.resize(m_adjacencyList.size(), 0);
}

Components Graph::GetComponents()
{
	SetTimeStamps();
	TimeSort();
	SetInvertedList();
	MarksComponents();

	return m_components;
}

void Graph::SetTimeStamps()
{
	size_t time = 1;
	for (size_t i = 0; i < m_visited.size(); i++)
	{
		if (!m_visited[i])
		{
			Dfs(i, time);
		}
	}
}

void Graph::Dfs(size_t vertex, size_t& time)
{
	if (m_visited[vertex])
	{
		return;
	}
	m_visited[vertex] = true;
	m_timeIn[vertex] = time++;
	for (const auto& edge : m_adjacencyList[vertex])
	{
		Dfs(edge, time);
	}
	m_timeOut[vertex] = time++;
}

void Graph::TimeSort()
{
	std::vector<std::pair<size_t, size_t>> sortedTime(m_timeOut.size());
	for (size_t i = 0; i < m_timeOut.size(); i++)
	{
		sortedTime[i] = { i, m_timeOut[i] };
	}
	std::sort(sortedTime.begin(), sortedTime.end(),
		[](std::pair<size_t, size_t> time1, std::pair<size_t, size_t> time2)
		{
			return time1.second > time2.second;
		});

	m_sortedTime = sortedTime;
}

void Graph::SetInvertedList()
{
	m_invertedList.resize(m_adjacencyList.size());
	for (size_t i = 0; i < m_adjacencyList.size(); i++)
	{
		for (const auto edge : m_adjacencyList[i])
		{
			m_invertedList[edge].push_back(i);
		}
	}
}

void Graph::MarksComponents()
{
	std::fill(m_visited.begin(), m_visited.end(), false);
	size_t componentNumber = 0;
	for (const auto& [vertex, time] : m_sortedTime)
	{
		if (!m_visited[vertex])
		{
			DfsOnInvertedGraph(vertex, componentNumber);
			componentNumber++;
		}		
	}
}

void Graph::DfsOnInvertedGraph(size_t vertex, size_t componentNumber)
{
	if (m_visited[vertex])
	{
		return;
	}

	m_visited[vertex] = true;
	m_components[componentNumber].push_back(vertex);

	for (const auto& edge : m_invertedList[vertex])
	{
		DfsOnInvertedGraph(edge, componentNumber);
	}
}

AdjacencyList Graph::GetAdjacencyListFromAdjacencyMatrix(const AdjacencyMatrix& matrix)
{
	AdjacencyList result(matrix.size());

	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix.size(); j++)
		{
			if (matrix[i][j] == 1)
			{
				result[i].push_back(j);
			}
		}
	}

	return result;
}


AdjacencyMatrix Graph::GetAdjacencyMatrixFromAdjacencyList(const AdjacencyList& adjList)
{
	size_t matrixSize = adjList.size();
	AdjacencyMatrix adjencyMatrix(matrixSize, std::vector<size_t>(matrixSize, 0));

	for (size_t i = 0; i < adjList.size(); i++)
	{
		for (const auto& edge : adjList[i])
		{
			adjencyMatrix[i][edge] = 1;
		}
	}

	return adjencyMatrix;
}