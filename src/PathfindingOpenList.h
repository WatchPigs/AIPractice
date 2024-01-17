#pragma once
#include "NodeRecord.h"
#include <queue>
#include <vector>
#include <functional>
#include <map>

class PathfindingOpenList
{
public:
	NodeRecord* SmallestElement();
	bool Contains(Node* node);
	NodeRecord* Find(Node* node);
	int Size();
	void Push(NodeRecord* node_record);
	void PopSmallestElement();

private:
	class Compare {
	public:
		bool operator()(NodeRecord* a, NodeRecord* b) { return a->estimated_total_cost > b->estimated_total_cost; }
	};
	std::priority_queue<NodeRecord*, std::vector<NodeRecord*>, Compare> node_record_priority_queue_;
	std::map<Node*, NodeRecord*> node_record_map_;
};
