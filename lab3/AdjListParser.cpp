#include "AdjListParser.h"

std::vector<std::vector<size_t>> ParseAdjList(std::istream& input)
{
	size_t vertexCount = 0, edgeCount = 0;
	if (!(input >> vertexCount >> edgeCount))
	{
		throw std::runtime_error("Invalid file format");
	}

	std::vector<std::vector<size_t>> adjList(vertexCount);
	for (size_t i = 0; i < edgeCount; i++)
	{
		size_t vertexOne = 0, vertexTwo = 0;
		if (!(input >> vertexOne >> vertexTwo) || vertexOne >= vertexCount)
		{
			throw std::runtime_error("Invalid file format");
		}
		adjList[vertexOne].push_back(vertexTwo);
		adjList[vertexTwo].push_back(vertexOne);
	}

	return adjList;
}