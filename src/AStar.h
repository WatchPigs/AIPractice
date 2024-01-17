#pragma once
#include "Connection.h"
#include <list>
#include "Graph.h"
#include "Heuristic.h"
#include <functional>

class AStar
{
public:
	static std::list<Connection*> PathfindAStar(Graph* graph, Node* start, Node* end, Heuristic* heuristic, std::function<void()> on_steps = NULL);
};

