#include "AdjListParser.h"
#include "Graph.h"
#include <fstream>
#include <iostream>

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
		graph.CheckPlanar();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
	}
}
