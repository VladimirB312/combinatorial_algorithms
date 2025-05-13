#include "Graph.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<std::vector<size_t>> ParseAdjList(std::istream& input)
{
	size_t vertexCount = 0, edgeCount = 0;
	if (!(input >> vertexCount >> edgeCount))
	{
		throw std::runtime_error("Invalid file format");
	}

	std::vector<std::vector<size_t>> adjList(vertexCount + 1);
	for (int i = 0; i < edgeCount; i++)
	{
		size_t v = 0, u = 0;
		if (!(input >> v >> u) || v > vertexCount || u > vertexCount)
		{
			throw std::runtime_error("Invalid file format");
		}
		adjList[v].push_back(u);
	}

	return adjList;
}

void CheckArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid arguments");
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		throw std::invalid_argument("Failed to open file");
	}
}

int main(int argc, char* argv[])
{
	try
	{
		CheckArgs(argc, argv);
		std::ifstream input(argv[1]);
		Graph graph(ParseAdjList(input));
		graph.FindMaxMatch();
		graph.PrintMatches();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
	}

	return 0;
}