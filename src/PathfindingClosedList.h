#pragma once
#include "NodeRecord.h"
#include <map>

class PathfindingClosedList
{
public:
	bool Contains(Node* node);
	NodeRecord* Find(Node* node);
	void Push(NodeRecord* node_record);
	void Remove(NodeRecord* node_record);
private:
	std::map<Node*, NodeRecord*> node_record_map_;
};

