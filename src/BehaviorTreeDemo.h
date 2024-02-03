#pragma once
#include "Boid.h"
#include "BehaviorTreeJR.h"
#include "CollisionDetector.h"
#include "DynamicObstacleAvoidance.h"
#include "DynamicLookWhereYoureGoing.h"

class BehaviorTreeDemo
{
public:
	Boid* character_boid_;
	BehaviorTreeJR* behavior_tree_jr_;

	CollisionDetector* collision_detector_;
	DynamicObstacleAvoidance* dynamic_obstacle_avoidance_;
	DynamicLookWhereYoureGoing* dynamic_look_where_youre_going_;

	enum ProcessControl
	{
		kReady = 0,
		kSetChargingStations = 1,
		kRunning = 2,
		kFinished = 3,
	};

	ProcessControl process_;

	bool mouse_clicked;

	BehaviorTreeDemo();

	void Setup();
	void Update();
	void Exit();
	void Draw();

	void DrawStrings();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
};

