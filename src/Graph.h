#pragma once
#include "Connection.h"
#include <vector>
#include <set>
#include <map>
class Graph
{
public:
	
	std::set<Node*> nodes_;
	std::set<Connection*> connections_;

	std::map<Node*, std::set<Connection*>> connections_from_nodes_;

	Graph();
	virtual ~Graph();

	// An array of connections outgoing from the given nodes
	virtual std::set<Connection*> GetConnections(Node* from_node);

	virtual bool RemoveNode(Node* node);
	virtual bool RemoveConnection(Connection* connection);

	virtual Connection* FindConnection(Node* from_node, Node* to_node);

	virtual bool AddNode(Node* node);
	virtual bool SetConnection(Node* from_node, Node* to_node, float cost);
};

