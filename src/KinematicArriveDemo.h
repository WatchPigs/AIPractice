#pragma once
#include "ofMain.h"
#include "Boid.h"
#include "Rigidbody.h"
#include <queue>
#include "KinematicArrive.h"

class KinematicArriveDemo
{
public:
	Boid* boid_;
	KinematicArrive* kinematic_arrive_ ;

	bool on_first_;
	std::queue<Rigidbody*> waypoints_;

	KinematicArriveDemo();

	void Setup();
	void Update();
	void Exit();
	void Draw();
};

