#include "PathfindingClosedList.h"

bool PathfindingClosedList::Contains(Node* node)
{
	if (node_record_map_.count(node)) return true;
	else return false;
}
NodeRecord* PathfindingClosedList::Find(Node* node)
{
	if (Contains(node)) return node_record_map_[node];
	else return nullptr;
}

void PathfindingClosedList::Push(NodeRecord* node_record)
{
	node_record_map_.insert(std::pair<Node*, NodeRecord*>(node_record->node, node_record));
	node_record->node->status = Node::kClosed;
}

void PathfindingClosedList::Remove(NodeRecord* node_record)
{
	node_record_map_.erase(node_record->node);
}
