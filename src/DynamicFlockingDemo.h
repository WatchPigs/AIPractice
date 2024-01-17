#pragma once
#include "ofMain.h"
#include "Boid.h"
#include "Rigidbody.h"
#include "DynamicWander.h"
#include "DynamicFlocking.h"
#include "CollisionDetector.h"
#include "DynamicObstacleAvoidance.h"
#include <vector>


class DynamicFlockingDemo
{
public:
	Boid* character_leader_boid_;
	std::vector<Boid*>	character_follower_boids_;

	DynamicWander* dynamic_wander_;
	CollisionDetector* collision_detector_;
	DynamicObstacleAvoidance* dynamic_obstacle_avoidance_leader_;
	std::vector<DynamicFlocking*> dynamic_flockings_;
	std::vector<DynamicObstacleAvoidance*> dynamic_obstacle_avoidance_followers_;

	DynamicFlockingDemo();

	void Setup();
	void Update();
	void Exit();
	void Draw();
};

