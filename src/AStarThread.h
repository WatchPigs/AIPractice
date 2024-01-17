#pragma once
#include "ofThread.h"
#include "Graph.h"
#include "Heuristic.h"
#include <list>

class AStarThread : public ofThread
{
public:
	Graph* graph_;
	Node* start_;
	Node* end_;
	Heuristic* heuristic_;

	bool finished_;
	int sleep_time_;
	std::list<Connection*> result_;

	AStarThread(int sleep_time);
	~AStarThread();

	void Init(Graph* graph, Node* start, Node* end, Heuristic* heuristic);
	void Sleep();

protected:
	void threadedFunction() override;

};

