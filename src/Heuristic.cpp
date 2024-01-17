#include "Heuristic.h"
#include "TileGraph.h"

float Heuristic::Estimate(Graph* graph, Node* current, Node* goal)
{
	switch (option_)
	{
	case Heuristic::kManhattanDistance:
		return ManhattanDistanceForTileGraph(graph, current, goal);
		break;
	default:
		break;
	}
}

Heuristic::Heuristic(HeuristicType option) :
	option_(option)
{
}

Heuristic::~Heuristic()
{
}

float Heuristic::Zero(Graph* graph, Node* current, Node* goal)
{
	return 0.0f;
}

float Heuristic::ManhattanDistanceForTileGraph(Graph* graph, Node* current, Node* goal)
{
	TileGraph* tile_graph = dynamic_cast<TileGraph*>(graph);
	TileNode* current_tile_node = dynamic_cast<TileNode*>(current);
	TileNode* goal_tile_node = dynamic_cast<TileNode*>(goal);
	if (tile_graph && current_tile_node && goal_tile_node)
	{
		glm::vec2 current_position = tile_graph->GetNodePosition(current_tile_node);
		glm::vec2 goal_position = tile_graph->GetNodePosition(goal_tile_node);

		return (abs(current_position.x - goal_position.x) + abs(current_position.y - goal_position.y)) / tile_graph->tile_size_;
	}
	else return 0;
}
