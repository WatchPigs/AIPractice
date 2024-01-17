#include "Dijkstra.h"
#include "NodeRecord.h"
#include "PathfindingOpenList.h"
#include "PathfindingClosedList.h"

std::list<Connection*> Dijkstra::PathfindDijkstra(Graph* graph, Node* start, Node* end, std::function<void()> on_steps)
{
	std::map<Node*, NodeRecord*> all_node_records;

	// Initialize the record for the start node.
	NodeRecord* start_record = new NodeRecord();
	start_record->node = start;
	start_record->connection = nullptr;
	start_record->cost_so_far = 0.0f;
	start_record->estimated_total_cost = start_record->cost_so_far;
	all_node_records.insert(std::pair<Node*, NodeRecord*>(start_record->node, start_record));

	// Initialize the open and closed lists.
	PathfindingOpenList* open = new PathfindingOpenList();
	open->Push(start_record);
	PathfindingClosedList* closed = new PathfindingClosedList();

	// Iterate through processing each node.
	NodeRecord* current = nullptr;
	while (open->Size() > 0)
	{
		// Find the smallest element in the open list.
		current = open->SmallestElement();

		// If it is the goal node, then terminate.
		if (current->node == end) break;

		// Otherwise get its outgoing connections.
		std::set<Connection*> connections = graph->GetConnections(current->node);

		// Loop through each connection in turn.
		for (Connection* connection : connections)
		{
			// Get the cost estimate for the end node.
			Node* end_node = connection->to_node_;
			float end_node_cost = current->cost_so_far + connection->cost_;

			NodeRecord* end_node_record = nullptr;
			// Skip if the node is closed.
			if (closed->Contains(end_node)) continue;
			// .. or if it is open and we have found a worse route.

			else if (open->Contains(end_node))
			{
				// Here we find the record in the open list corresponding to the endNode.
				end_node_record = open->Find(end_node);
				if (end_node_record->cost_so_far <= end_node_cost) continue;
			}

			// Otherwise we know we have got an unvisited node, so make a record for it.
			else
			{
				end_node_record = new NodeRecord();
				end_node_record->node = end_node;
				all_node_records.insert(std::pair<Node*, NodeRecord*>(end_node_record->node, end_node_record));
			}

			// We are here if we need to update the node. Update the cost and connection.
			end_node_record->cost_so_far = end_node_cost;
			end_node_record->estimated_total_cost = end_node_record->cost_so_far;
			end_node_record->connection = connection;

			// And add it to the open list.
			if (!open->Contains(end_node)) 
			{
				if (on_steps) on_steps();
				open->Push(end_node_record);
			}
		}
		
		// We have finished looking at the connections for the current node, so add it to the closed list and remove it from the open list.
		if (on_steps) on_steps();
		open->PopSmallestElement();
		closed->Push(current);
	}

	delete open;
	delete closed;

	// We are here if we have either found the goal, or if we have no more nodes to search, find which.
	if (current == nullptr || current->node != end)
	{
		// We have run out of nodes without finding the goal, so there is no solution.
		for (std::pair<Node*, NodeRecord*> node_record_pair : all_node_records) delete node_record_pair.second;
		return std::list<Connection*>();
	}
	else
	{
		// Compile the list of connections in the path.
		auto path = std::list<Connection*>();

		// Work back along the path, accumulating connections.
		while (current->node != start)
		{
			path.push_back(current->connection);
			current = all_node_records[current->connection->from_node_];
		}

		for (std::pair<Node*, NodeRecord*> node_record_pair : all_node_records) delete node_record_pair.second;

		// Reverse the path, and return it.
		path.reverse();
		return path;
	}
}
