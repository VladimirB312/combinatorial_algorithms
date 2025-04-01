#include "Graph.h"
#include "SegmentSearcher.h"

Graph::Graph(const std::vector<std::vector<size_t>>& adjList)
	: m_adjList(adjList)
{
	m_adjMatrix = (GetAdjMatrixFromAdjList(adjList));
};

void Graph::CheckPlanar()
{
	std::vector<size_t> firstVerge = FindFirstCycle();
	m_verges.push_back(firstVerge);
	m_verges.push_back(firstVerge);
	DeleteEdges(firstVerge);
	FindAndInsertSegments();
}

void Graph::DeleteEdges(const std::vector<size_t>& vertices)
{
	m_adjMatrix[vertices[0]][vertices[vertices.size() - 1]] = 0;
	m_adjMatrix[vertices[vertices.size() - 1]][vertices[0]] = 0;
	for (size_t i = 0; i < vertices.size(); i++)
	{
		if (i + 1 < vertices.size())
		{
			m_adjMatrix[vertices[i]][vertices[i + 1]] = 0;
			m_adjMatrix[vertices[i + 1]][vertices[i]] = 0;
		}
	}
}

std::set<size_t> Graph::GetContactVertices()
{
	std::set<size_t> contactVertices;
	for (const auto& verge : m_verges)
	{
		for (auto vertex : verge)
		{
			if (std::any_of(m_adjMatrix[vertex].begin(), m_adjMatrix[vertex].end(),
					[](size_t x) {
						return x == 1;
					}))
			{
				contactVertices.insert(vertex);
			}
		}
	}

	return contactVertices;
}

std::vector<std::vector<size_t>> Graph::FindSegments()
{
	std::set<size_t> contactVertices = GetContactVertices();
	SegmentSearcher segFounder(contactVertices, m_adjMatrix);
	std::vector<std::vector<size_t>> segments = segFounder.GetAllSegments();

	return segments;
}

std::map<size_t, std::vector<size_t>> Graph::GetSegmentsInVerges(const std::vector<std::vector<size_t>>& segments)
{
	std::map<size_t, std::vector<size_t>> segmentsInVerges;
	for (size_t s = 0; s < segments.size(); s++)
	{
		for (size_t v = 0; v < m_verges.size(); v++)
		{
			if (IsVergeContainSegment(m_verges[v], segments[s]))
			{
				segmentsInVerges[s].push_back(v);
			}
		}
	}

	return segmentsInVerges;
}

std::pair<size_t, std::vector<size_t>> Graph::GetSegmentMinOfVerges(
	const std::map<size_t, std::vector<size_t>>& segCountInVerges)
{
	auto segmentMinOfVerges = std::min_element(segCountInVerges.begin(),
		segCountInVerges.end(),
		[](auto& v1, auto& v2) {
			return v1.second.size() < v2.second.size();
		});

	if (segmentMinOfVerges->second.empty())
	{
		throw std::runtime_error("Graph is not planar");
	}

	return *segmentMinOfVerges;
}

void Graph::FindAndInsertSegments()
{
	std::vector<std::vector<size_t>> segments = FindSegments();
	while (!segments.empty())
	{
		std::map<size_t, std::vector<size_t>> segCountInVerges = GetSegmentsInVerges(segments);
		if (segCountInVerges.empty())
		{
			throw std::runtime_error("Graph is not planar");
		}
		std::pair<size_t, std::vector<size_t>> minVergeSegment = GetSegmentMinOfVerges(segCountInVerges);
		InsertSegmentIntoVerge(segments[minVergeSegment.first], minVergeSegment.second[0]);
		DeleteEdges(segments[minVergeSegment.first]);
		segments = FindSegments();
	}

	std::cout << "Graph is planar. Verges:\n";
	PrintVerges();
}

void Graph::PrintVerges()
{
	for (const auto& verge : m_verges)
	{
		std::cout << "Verge: ";
		for (auto v : verge)
		{
			std::cout << v << " ";
		}
		std::cout << "\n";
	}
}

void Graph::InsertSegmentIntoVerge(const std::vector<size_t>& segment, size_t vergeNum)
{
	auto verge = m_verges[vergeNum];
	std::vector<size_t> newVerge1 = segment;
	std::vector<size_t> newVerge2 = segment;
	bool startRec = false;
	for (size_t i = 0; !startRec || newVerge1[0] != verge[i]; i = (i + 1) % verge.size())
	{
		if (startRec)
		{
			newVerge1.push_back(verge[i]);
		}
		if (!startRec && newVerge1[newVerge1.size() - 1] == verge[i])
		{
			startRec = true;
		}
	}

	startRec = false;
	for (size_t i = verge.size() - 1; !startRec || newVerge2[0] != verge[i]; i = i == 0 ? verge.size() - 1 : i - 1)
	{
		if (startRec)
		{
			newVerge2.push_back(verge[i]);
		}
		if (!startRec && newVerge2[newVerge2.size() - 1] == verge[i])
		{
			startRec = true;
		}
	}

	m_verges[vergeNum] = newVerge1;
	m_verges.push_back(newVerge2);
}

bool Graph::IsVergeContainSegment(const std::vector<size_t>& verge, const std::vector<size_t>& seg)
{
	return std::find(verge.begin(), verge.end(), seg[0]) != verge.end() && std::find(verge.begin(), verge.end(), seg[seg.size() - 1]) != verge.end();
}

std::vector<size_t> Graph::FindFirstCycle()
{
	std::vector<bool> visited(m_adjList.size(), false);
	std::vector<size_t> from(m_adjList.size(), INT_MAX);
	std::vector<size_t> cycle;
	FindFirstCycle(0, visited, from, cycle);

	if (cycle.empty())
	{
		throw std::runtime_error("graph hasn't cycle");
	}

	return cycle;
}

std::vector<size_t> Graph::GetWayBack(std::vector<size_t>& from, size_t lastVertex)
{
	std::vector<size_t> cycle;
	for (size_t v = from[lastVertex]; v != lastVertex; v = from[v])
	{
		cycle.push_back(v);
	}
	cycle.push_back(lastVertex);
	std::reverse(cycle.begin(), cycle.end());

	return cycle;
}

void Graph::FindFirstCycle(size_t curr, std::vector<bool>& visited, std::vector<size_t>& from, std::vector<size_t>& cycle)
{
	visited[curr] = true;

	for (auto vertex : m_adjList[curr])
	{
		if (vertex == from[curr])
		{
			continue;
		}
		from[vertex] = curr;
		if (visited[vertex])
		{
			cycle = GetWayBack(from, vertex);
			return;
		}
		FindFirstCycle(vertex, visited, from, cycle);
		break;
	}
}

std::vector<std::vector<size_t>> Graph::GetAdjMatrixFromAdjList(const std::vector<std::vector<size_t>>& adjList)
{
	std::vector<std::vector<size_t>> adjMatrix(adjList.size(), std::vector<size_t>(adjList.size(), 0));

	for (size_t i = 0; i < adjList.size(); i++)
	{
		for (const auto& vertex : adjList[i])
		{
			adjMatrix[i][vertex] = 1;
			adjMatrix[vertex][i] = 1;
		}
	}

	return adjMatrix;
}
