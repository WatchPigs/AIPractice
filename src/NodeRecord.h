#pragma once
#include "Node.h"
#include "Connection.h"

// In Dijkstra pathfinder, this structure is used to keep track of the information we need for each node.
struct NodeRecord
{
	Node* node;
	Connection* connection;
	float cost_so_far;
	float estimated_total_cost; // equals to cost_so_far for Dijkstra

	//inline bool operator < (const NodeRecord& rhs)
	//{
	//	if (cost_so_far < rhs.cost_so_far) return true;
	//	else return false;
	//}

	//inline bool operator > (const NodeRecord& rhs)
	//{
	//	if (cost_so_far > rhs.cost_so_far) return true;
	//	else return false;
	//}
};

