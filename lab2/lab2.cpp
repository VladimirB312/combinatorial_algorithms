#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "Graph.h"

void CheckArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid argument count");
	}

	std::ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Failed to open file of graph");
	}
}

std::vector<std::vector<size_t>> ParseAdjacencyList(std::istream& input)
{
	size_t vertexCount, edgeCount;
	input >> vertexCount >> edgeCount;
	std::vector<std::vector<size_t>> adjList(vertexCount);
	for (size_t i = 0; i < edgeCount; i++)
	{
		size_t vertex, edge;
		input >> vertex >> edge;
		adjList[vertex].push_back(edge);
	}

	return adjList;
}

void PrintComponents(std::ostream& output, const Components& components)
{
	for (const auto& [component, vertices] : components)
	{
		std::cout << component << ": ";
		bool isFirst = true;
		for (auto vertex : vertices)
		{
			if (!isFirst)
			{
				std::cout << ", ";
			}
			std::cout << vertex;
			isFirst = false;
		}
		std::cout << "\n";
	}
}

int main(int argc, char* argv[])
{
	try {
		CheckArgs(argc, argv);
		std::ifstream inputFile(argv[1]);
		Graph graph(ParseAdjacencyList(inputFile));
		Components components = graph.GetComponents();
		PrintComponents(std::cout, components);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}