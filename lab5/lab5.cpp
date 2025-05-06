#include "Network.h"
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> ParseCapacityMatrix(std::istream& input)
{
	size_t vertexCount = 0, edgeCount = 0;
	if (!(input >> vertexCount >> edgeCount))
	{
		throw std::runtime_error("Invalid file format");
	}

	std::vector capacityList(vertexCount, std::vector<int>(vertexCount));
	for (int i = 0; i < edgeCount; i++)
	{
		size_t v = 0, u = 0;
		int c = 0;
		if (!(input >> v >> u >> c) || v >= vertexCount)
		{
			throw std::runtime_error("Invalid file format");
		}
		capacityList[v][u] = c;
	}

	return capacityList;
}

void PrintMatrix(const std::vector<std::vector<int>>& matrix)
{
	for (auto& row : matrix)
	{
		for (auto col : row)
		{
			if (col < 0)
			{
				col = 0;
			}
			std::cout << std::format("{:3}", col) << " ";
		}
		std::cout << "\n";
	}
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
		Network net(ParseCapacityMatrix(input));
		PrintMatrix(net.FindMaxFlow());
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
	}

	return 0;
}
