#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using Edge = std::pair<size_t, size_t>;

class Graph
{
public:
	explicit Graph(const std::vector<std::vector<size_t>>& adjList);

	void CheckPlanar();

private:
	std::vector<std::vector<size_t>> m_adjMatrix{};
	std::vector<std::vector<size_t>> m_adjList{};
	std::vector<Edge> m_edges;
	std::vector<std::vector<size_t>> m_verges;

	void DeleteEdges(const std::vector<size_t>& vertices);
	std::set<size_t> GetContactVertices();
	std::vector<std::vector<size_t>> FindSegments();
	std::map<size_t, std::vector<size_t>> GetSegmentsInVerges(const std::vector<std::vector<size_t>>& segments);
	std::pair<size_t, std::vector<size_t>> GetSegmentMinOfVerges(const std::map<size_t, std::vector<size_t>>& segCountInVerges);
	void FindAndInsertSegments();
	void PrintVerges();
	void InsertSegmentIntoVerge(const std::vector<size_t>& segment, size_t vergeNum);
	bool IsVergeContainSegment(const std::vector<size_t>& verge, const std::vector<size_t>& seg);
	std::vector<size_t> FindFirstCycle();
	std::vector<size_t> GetWayBack(std::vector<size_t>& from, size_t lastVertex);
	void FindFirstCycle(size_t curr, std::vector<bool>& visited, std::vector<size_t>& from, std::vector<size_t>& cycle);
	std::vector<std::vector<size_t>> GetAdjMatrixFromAdjList(const std::vector<std::vector<size_t>>& adjList);
};
