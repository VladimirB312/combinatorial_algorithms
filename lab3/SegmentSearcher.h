#pragma once
#include <set>
#include <vector>

class SegmentSearcher
{
public:
	SegmentSearcher(const std::set<size_t>& contactVertexes, const std::vector<std::vector<size_t>>& adjMatrix);

	std::vector<std::vector<size_t>> GetAllSegments();

private:
	const std::set<size_t>& m_contactVertexes;
	const std::vector<std::vector<size_t>>& m_adjMatrix;
	std::vector<bool> m_visited;
	std::vector<size_t> m_from;

	void GetSegmentsFromVertex(size_t vertex, std::vector<std::vector<size_t>>& segments);
	void FindSegment(size_t curr, std::vector<std::vector<size_t>>& segments);
	std::vector<size_t> GetSegmentCycle(std::vector<size_t>& from, size_t lastVertex);
};
