#include "DijkstraThread.h"
#include "Dijkstra.h"

DijkstraThread::DijkstraThread(int sleep_time) :
	graph_(nullptr), start_(nullptr), end_(nullptr), finished_(false), sleep_time_(sleep_time), result_(NULL)
{
}

DijkstraThread::~DijkstraThread()
{
}

void DijkstraThread::Init(Graph* graph, Node* start, Node* end)
{
	graph_ = graph;
	start_ = start;
	end_ = end;
}

void DijkstraThread::Sleep()
{
	sleep(sleep_time_);
}


void DijkstraThread::threadedFunction()
{
	std::function<void()> SleepFunc = std::bind(&DijkstraThread::Sleep, this);
	result_ = Dijkstra::PathfindDijkstra(graph_, start_, end_, SleepFunc);
	finished_ = true;
}