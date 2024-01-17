#pragma once
#include "Graph.h"

class Heuristic
{
public:
	enum HeuristicType
	{
		KZero = 0,
		kManhattanDistance = 1,
	};

	HeuristicType option_;

	float Estimate(Graph* graph, Node* current, Node* goal);

	Heuristic(HeuristicType option);
	~Heuristic();
private:
	float Zero(Graph* graph, Node* current, Node* goal);
	float ManhattanDistanceForTileGraph(Graph* graph, Node* current, Node* goal);

};

