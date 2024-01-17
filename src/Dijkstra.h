#pragma once
#include "Connection.h"
#include <list>
#include "Graph.h"
#include <functional>

class Dijkstra
{
public:
	static std::list<Connection*> PathfindDijkstra(Graph* graph, Node* start, Node* end, std::function<void()> on_steps = NULL);
};

