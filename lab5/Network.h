#pragma once
#include <algorithm>
#include <list>
#include <vector>

class Network
{
public:
	explicit Network(const std::vector<std::vector<int>>& capacityList);

	std::vector<std::vector<int>> FindMaxFlow();

private:
	std::vector<std::vector<int>> m_capacity;
	std::vector<std::vector<int>> m_flow;
	std::vector<int> m_excess;
	std::vector<size_t> m_height;
	std::list<size_t> m_nodeList;
	std::vector<size_t> m_current;

	void InitializePreflow();
	void Push(size_t u, size_t v);
	void Relabel(size_t u);
	void Discharge(size_t u);
	void InitializeNodeList();
	void RelabelToFront();
};
