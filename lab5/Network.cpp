#include "Network.h"

Network::Network(const std::vector<std::vector<int>>& capacityList)
	: m_capacity(capacityList)
	, m_flow(capacityList.size(), std::vector<int>(capacityList.size(), 0))
	, m_excess(capacityList.size(), 0)
	, m_height(capacityList.size(), 0)
	, m_current(capacityList.size(), 0)
{
}

void Network::InitializePreflow()
{
	m_height[0] = m_capacity.size();
	for (size_t i = 0; i < m_flow.size(); i++)
	{
		if (m_capacity[0][i])
		{
			m_flow[0][i] = m_capacity[0][i];
			m_flow[i][0] = -m_capacity[0][i];
			m_excess[i] = m_capacity[0][i];
			m_excess[0] -= m_capacity[0][i];
		}
	}
}

void Network::Push(size_t u, size_t v)
{
	int delta = std::min(m_excess[u], m_capacity[u][v] - m_flow[u][v]);
	m_flow[u][v] += delta;
	m_flow[v][u] -= delta;
	m_excess[u] -= delta;
	m_excess[v] += delta;
}

void Network::Relabel(size_t u)
{
	size_t minHeight = SIZE_MAX;
	for (size_t i = 0; i < m_capacity.size(); i++)
	{
		if (m_capacity[u][i] - m_flow[u][i] > 0 && m_height[i] < minHeight)
		{
			minHeight = m_height[i];
		}
	}
	m_height[u] = minHeight + 1;
}

void Network::Discharge(size_t u)
{
	while (m_excess[u] > 0)
	{
		size_t v = m_current[u];
		if (v < m_current.size())
		{
			if (m_capacity[u][v] - m_flow[u][v] > 0 && m_height[u] > m_height[v])
			{
				Push(u, v);
			}
			else
			{
				m_current[u]++;
			}
		}
		else
		{
			Relabel(u);
			m_current[u] = 0;
		}
	}
}

void Network::InitializeNodeList()
{
	for (size_t i = 1; i < m_capacity.size() - 1; i++)
	{
		m_nodeList.push_back(i);
	}
}

void Network::RelabelToFront()
{
	InitializePreflow();
	InitializeNodeList();
	auto pointer = m_nodeList.begin();
	while (pointer != m_nodeList.end())
	{
		size_t u = *pointer;
		size_t oldHeight = m_height[u];
		Discharge(u);
		if (oldHeight < m_height[u])
		{
			m_nodeList.erase(pointer);
			m_nodeList.push_front(u);
			pointer = m_nodeList.begin();
		}
		else
		{
			++pointer;
		}
	}
}

std::vector<std::vector<int>> Network::FindMaxFlow()
{
	RelabelToFront();
	return m_flow;
}
