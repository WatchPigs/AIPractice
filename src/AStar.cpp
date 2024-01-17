#include "AStar.h"
#include "NodeRecord.h"
#include "PathfindingOpenList.h"
#include "PathfindingClosedList.h"


std::list<Connection*> AStar::PathfindAStar(Graph* graph, Node* start, Node* end, Heuristic* heuristic, std::function<void()> on_steps)
{
	std::map<Node*, NodeRecord*> all_node_records;

	// Initialize the record for the start node.
	NodeRecord* start_record = new NodeRecord();
	start_record->node = start;
	start_record->connection = nullptr;
	start_record->cost_so_far = 0.0f;
	start_record->estimated_total_cost = heuristic->Estimate(graph, start, end);
	all_node_records.insert(std::pair<Node*, NodeRecord*>(start_record->node, start_record));

	// Initialize the open and closed lists.
	PathfindingOpenList* open = new PathfindingOpenList();
	open->Push(start_record);
	PathfindingClosedList* closed = new PathfindingClosedList();

	// Iterate through processing each node.
	NodeRecord* current = nullptr;
	while (open->Size() > 0)
	{
		// Find the smallest element in the open list (using the estimatedTotalCost).
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
			float end_node_heuristic;
			// If the node is closed we may have to skip, or remove it from the closed list.
			if (closed->Contains(end_node))
			{
				// Here we find the record in the closed list corresponding to the endNode.
				end_node_record = closed->Find(end_node);

				// If we did not find a shorter route, skip.
				if (end_node_record->cost_so_far <= end_node_cost) continue;

				// Otherwise remove it from the closed list.
				closed->Remove(end_node_record);

				// We can use the nodes old cost values to calculate its heuristic without calling the possibly expensive heuristic function.
				end_node_heuristic = end_node_record->estimated_total_cost - end_node_record->cost_so_far;
			}

			// Skip if the node is open and we have not found a better route.
			else if (open->Contains(end_node))
			{
				// Here we find the record in the open list corresponding to the endNode.
				end_node_record = open->Find(end_node);

				// If our route is no better, then skip.
				if (end_node_record->cost_so_far <= end_node_cost) continue;

				// Again, we can calculate its heuristic.
				end_node_heuristic = end_node_record->estimated_total_cost - end_node_record->cost_so_far;
			}

			// Otherwise we know we have got an unvisited node, so make a record for it.
			else
			{
				end_node_record = new NodeRecord();
				end_node_record->node = end_node;
				all_node_records.insert(std::pair<Node*, NodeRecord*>(end_node_record->node, end_node_record));

				//  We will need to calculate the heuristic value using the function, since we don¡¯t have an existing record to use.
				end_node_heuristic = heuristic->Estimate(graph, end_node, end);
			}

			// We are here if we need to update the node. Update the cost, estimate and connection.
			end_node_record->cost_so_far = end_node_cost;
			end_node_record->connection = connection;
			end_node_record->estimated_total_cost = end_node_cost + end_node_heuristic;

			// And add it to the open list
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
