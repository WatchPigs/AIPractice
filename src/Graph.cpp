#include "Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
	for (Node* node : nodes_) delete node;
	for (Connection* connection : connections_) delete connection;
}

std::set<Connection*> Graph::GetConnections(Node* from_node)
{
	if (connections_from_nodes_.count(from_node) == 1) return connections_from_nodes_[from_node];
	else return std::set<Connection*>();
}

bool Graph::RemoveNode(Node* node)
{
	if (node != nullptr && nodes_.count(node) == 1)
	{
		std::set<Connection*> connections_to_remove_from_node = connections_from_nodes_[node];
		std::set<Connection*> connections_to_remove_to_node;
		for (auto connection : connections_to_remove_from_node)
		{
			Connection* connection_to_node = FindConnection(connection->to_node_, connection->from_node_);
			if (connection_to_node != nullptr) connections_to_remove_to_node.insert(connection_to_node);
		}
		for (auto connection : connections_to_remove_from_node) RemoveConnection(connection);
		for (auto connection : connections_to_remove_to_node) RemoveConnection(connection);
		nodes_.erase(node);
		connections_from_nodes_.erase(node);
		delete node;
		return true;
	}
	return false;
}

bool Graph::RemoveConnection(Connection* connection)
{
	if (connection != nullptr && connections_.count(connection) == 1)
	{
		connections_.erase(connection);
		connections_from_nodes_[connection->from_node_].erase(connection);
		delete connection;
		return true;
	}
	return false;
}

Connection* Graph::FindConnection(Node* from_node, Node* to_node)
{
	if (nodes_.count(from_node) == 1 && nodes_.count(to_node) == 1)
	{
		for (auto connection : connections_from_nodes_[from_node])
		{
			if (connection->to_node_ == to_node) return connection;
		}
	}
	return nullptr;
}

bool Graph::AddNode(Node* node)
{
	if (node != nullptr && nodes_.count(node) == 0)
	{
		nodes_.insert(node);
		connections_from_nodes_.insert(std::pair<Node*, std::set<Connection*>>(node, std::set<Connection*>()));
	}
	else return false;
}

bool Graph::SetConnection(Node* from_node, Node* to_node, float cost)
{
	if (nodes_.count(from_node) == 1 && nodes_.count(to_node) == 1)
	{
		bool existed = false;

		for (auto connection : connections_from_nodes_[from_node])
		{
			if (connection->to_node_ == to_node)
			{
				connection->cost_ = cost;
				existed = true;
				break;
			}
		}
		if (!existed) 
		{
			Connection* new_connection = new Connection(from_node, to_node, cost);
			connections_.insert(new_connection);
			connections_from_nodes_[from_node].insert(new_connection);
		}
		return true;
	}
	else return false;
}

