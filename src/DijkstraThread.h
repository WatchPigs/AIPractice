#pragma once
#include "ofThread.h"
#include "Graph.h"
#include <list>

class DijkstraThread : public ofThread
{
public:
	Graph* graph_;
	Node* start_;
	Node* end_;
	bool finished_;
	int sleep_time_;
	std::list<Connection*> result_;

	DijkstraThread(int sleep_time);
	~DijkstraThread();

	void Init(Graph* graph, Node* start, Node* end);
	void Sleep();

protected:
	void threadedFunction() override;

};

