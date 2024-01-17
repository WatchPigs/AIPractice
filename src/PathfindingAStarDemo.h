#pragma once
#include "TileGraph.h"
#include "Heuristic.h"
#include "AStarThread.h"

class PathfindingAStarDemo
{
public:
	TileGraph* tile_graph_;
	Node* start_node_;
	Node* end_node_;

	Heuristic* heuristic_;

	AStarThread* a_star_thread_;

	enum ProcessControl
	{
		kReady = 0,
		kSetObstacles = 1,
		kSetStart = 2,
		kSetEnd = 3,
		kStartProcess = 4,
		kProcessing = 5,
		kFinished = 6,
	};

	ProcessControl process_;

	PathfindingAStarDemo();

	void Setup();
	void Update();
	void Exit();
	void Draw();

	void SetPathNodes(std::list<Connection*> result);

	void DrawStrings();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
};

