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
};

