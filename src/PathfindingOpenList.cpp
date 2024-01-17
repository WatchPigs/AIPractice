#include "PathfindingOpenList.h"
#include "ofLog.h"

NodeRecord* PathfindingOpenList::SmallestElement()
{
	return node_record_priority_queue_.top();
}

bool PathfindingOpenList::Contains(Node* node)
{
	if (node_record_map_.count(node)) return true;
	else return false;
}

NodeRecord* PathfindingOpenList::Find(Node* node)
{
	if (Contains(node)) return node_record_map_[node];
	else return nullptr;
}

int PathfindingOpenList::Size()
{
	return node_record_priority_queue_.size();
}

void PathfindingOpenList::Push(NodeRecord* node_record)
{
	node_record_priority_queue_.push(node_record);
	node_record_map_.insert(std::pair<Node*, NodeRecord*>(node_record->node, node_record));
	node_record->node->status = Node::kOpen;
}

void PathfindingOpenList::PopSmallestElement()
{
	node_record_map_.erase(node_record_priority_queue_.top()->node);
	node_record_priority_queue_.pop();
}
