#pragma once
#include "Node.h"

class Connection
{
public:
	// The node that this connection came from.
	Node* from_node_;

	// The node that this connection leads to.
	Node* to_node_;

	// The non-negative cost of this connection.
	float cost_;

	Connection() = delete;

	Connection(Node* from_node, Node* to_node, float cost);
};

