#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../Graph.h"

SCENARIO("Get stringly connected components of graph")
{
	WHEN("graph does not contain vertices")
	{
		AdjacencyList adjList;

		Graph graph(adjList);
		Components components = graph.GetComponents();
		THEN("graph does not contain a connected component")
		{
			CHECK(components.empty());
		}
	}

	WHEN("graph contain 3 vertices and not contain edges")
	{
		AdjacencyList adjList(3);

		Graph graph(adjList);
		Components components = graph.GetComponents();
		THEN("components must be for each vertex")
		{
			CHECK(components.size() == 3);
		}
	}

	WHEN("graph contain 3 vertices and one component")
	{
		AdjacencyList adjList = {
			{{1}}, // 0 -> 1
			{{2}}, // 1 -> 2
			{{0}}, // 2 -> 0
		};

		Graph graph(adjList);
		Components components = graph.GetComponents();
		auto vertices = components[0];
		std::sort(vertices.begin(), vertices.end());
		THEN("components must be one and contain all vertices")
		{
			CHECK(components.size() == 1);
			CHECK(vertices == std::vector<size_t>{0, 1, 2});
		}
	}

	WHEN("graph contain 3 vertices and two component")
	{
		AdjacencyList adjList = {
			{{1}}, // 0 -> 1
			{{0}}, // 1 -> 0
			{{}}, // 2
		};

		Graph graph(adjList);
		Components components = graph.GetComponents();
		auto vertices1 = components[0];
		auto vertices2 = components[1];
		std::sort(vertices2.begin(), vertices2.end());
		THEN("components must be two and they must contain vertices")
		{
			CHECK(components.size() == 2);
			CHECK(vertices2 == std::vector<size_t>{0, 1});
			CHECK(vertices1 == std::vector<size_t>{2});
		}
	}

	WHEN("graph contain 5 vertices and one component")
	{
		AdjacencyList adjList = {
			{{1}}, // 0 -> 1
			{{4}}, // 1 -> 4
			{{1, 4}}, // 2 -> 1, 4
			{{0}}, // 3 -> 0
			{{2, 3}} // 4 -> 2, 3
		};

		Graph graph(adjList);
		Components components = graph.GetComponents();
		auto vertices = components[0];
		std::sort(vertices.begin(), vertices.end());
		THEN("components must be contain one component")
		{
			CHECK(components.size() == 1);
			CHECK(vertices == std::vector<size_t>{0, 1, 2, 3, 4});
		}
	}
}