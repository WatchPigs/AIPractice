#pragma once
#include "ofMain.h"
#include "Boid.h"
#include "Rigidbody.h"
#include "DynamicWander.h"
#include "DynamicObstacleAvoidance.h"

class DynamicWanderDemo
{
public:
	Boid* character_boid_;
	DynamicWander* dynamic_wander_;
	CollisionDetector* collision_detector_;
	DynamicObstacleAvoidance* dynamic_obstacle_avoidance_;


	DynamicWanderDemo();

	void Setup();
	void Update();
	void Exit();
	void Draw();
};

