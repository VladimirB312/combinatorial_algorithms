#include "Graph.h"
#include <sstream>

Graph::Graph(const AdjacencyMatrix& matrix)
	: adjacencyMatrix(matrix), dimension(matrix.size())
{
	visited = std::vector<bool>(dimension, false);
}

void Graph::PrintTimeStamps(std::ostream& output)
{
	for (const auto& [key, value] : timeStamps)
	{
		output << "Vertex " << key << ": IN = " << value.in << " OUT = " << value.out << "\n";
	}
}

void Graph::SetTimeStamps()
{
	size_t time = 0;
	DfsMatrix(0, time);
}

void Graph::DfsMatrix(size_t vertex, size_t& time)
{
	if (visited[vertex])
	{
		return;
	}
	visited[vertex] = true;
	timeStamps[vertex].in = time++;
	for (size_t i = 0; i < dimension; i++)
	{
		if (adjacencyMatrix[vertex][i] == 1)
		{
			DfsMatrix(i, time);
		}
	}
	timeStamps[vertex].out = time++;
}

AdjacencyList Graph::GetAdjacencyListFromAdjacencyMatrix()
{
	AdjacencyList result{};

	for (size_t i = 0; i < dimension; i++)
	{
		for (size_t j = 0; j < dimension; j++)
		{
			if (adjacencyMatrix[i][j] == 1)
			{
				result[i].push_back(j);
			}
		}
	}
}

size_t Graph::GetMaxVertexNumber() 
{
	size_t maxVertexNumber = 0;
	for (const auto& [vertex, edgeList] : adjacencyList)
	{
		if (vertex > maxVertexNumber)
		{
			maxVertexNumber = vertex;
		}
		for (const auto& edge : edgeList)
		{
			if (edge > maxVertexNumber)
			{
				maxVertexNumber = edge;
			}
		}
	}

	return maxVertexNumber;
}

AdjacencyMatrix Graph::GetAdjacencyMatrixFromAdjacencyList()
{
	size_t maxVertexNumber = GetMaxVertexNumber();
	AdjacencyMatrix result(maxVertexNumber + 1, std::vector<size_t>(maxVertexNumber + 1, 0));

	for (const auto& [vertex, edgeList] : adjacencyList)
	{
		for (const auto& edge : edgeList)
		{
			result[vertex][edge] = 1;
		}
	}

	return result;
}