#include "AStarThread.h"
#include "AStar.h"


AStarThread::AStarThread(int sleep_time) :
	graph_(nullptr), start_(nullptr), end_(nullptr), heuristic_(nullptr), finished_(false), sleep_time_(sleep_time), result_(NULL)
{
}

AStarThread::~AStarThread()
{

}

void AStarThread::Init(Graph* graph, Node* start, Node* end, Heuristic* heuristic)
{
	graph_ = graph;
	start_ = start;
	end_ = end;
	heuristic_ = heuristic;
}

void AStarThread::Sleep()
{
	sleep(sleep_time_);
}


void AStarThread::threadedFunction()
{
	std::function<void()> SleepFunc = std::bind(&AStarThread::Sleep, this);
	result_ = AStar::PathfindAStar(graph_, start_, end_, heuristic_, SleepFunc);
	finished_ = true;
}