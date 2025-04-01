#include "SegmentSearcher.h"
#include <algorithm>
#include <climits>

SegmentSearcher::SegmentSearcher(const std::set<size_t>& contactVertexes,
	const std::vector<std::vector<size_t>>& adjMatrix)
	: m_contactVertexes(contactVertexes)
	, m_adjMatrix(adjMatrix)
{
	m_visited.resize(adjMatrix.size());
	m_from.resize(adjMatrix.size());
}

std::vector<std::vector<size_t>> SegmentSearcher::GetAllSegments()
{
	std::vector<std::vector<size_t>> segments;
	for (const auto& vertex : m_contactVertexes)
	{
		GetSegmentsFromVertex(vertex, segments);
	}

	return segments;
}

void SegmentSearcher::GetSegmentsFromVertex(size_t vertex, std::vector<std::vector<size_t>>& segments)
{
	std::fill(m_visited.begin(), m_visited.end(), false);
	std::fill(m_from.begin(), m_from.end(), INT_MAX);

	FindSegment(vertex, segments);
}

void SegmentSearcher::FindSegment(size_t curr, std::vector<std::vector<size_t>>& segments)
{
	m_visited[curr] = true;
	for (size_t i = 0; i < m_adjMatrix[curr].size(); i++)
	{
		if (m_adjMatrix[curr][i] == 0)
		{
			continue;
		}
		// если вершина контактная - проверяем откуда пришли (если не из предыдшествующей или из контактной то добавляем сегмент)
		if (m_contactVertexes.contains(i) && (m_from[curr] != i || m_contactVertexes.contains(curr)))
		{
			m_from[i] = curr;
			segments.push_back(GetSegmentCycle(m_from, i));
			continue;
		}
		if (m_from[curr] == i || m_visited[i])
		{
			continue;
		}
		m_from[i] = curr;
		FindSegment(i, segments);
	}
}

std::vector<size_t> SegmentSearcher::GetSegmentCycle(std::vector<size_t>& from, size_t lastVertex)
{
	std::vector<size_t> cycle;
	for (size_t v = lastVertex; v != INT_MAX; v = from[v])
	{
		cycle.push_back(v);
	}
	std::reverse(cycle.begin(), cycle.end());

	return cycle;
}
