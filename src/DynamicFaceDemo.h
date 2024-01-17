#pragma once
#include "ofMain.h"
#include "Boid.h"
#include "Rigidbody.h"
#include <vector>
#include "KinematicArrive.h"
#include "DynamicFace.h"


class DynamicFaceDemo
{
public:
	Boid* character_face_boid_;
	Boid* target_boid_;
	KinematicArrive* kinematic_arrive_;
	DynamicFace* dynamic_face_;

	std::vector<Rigidbody*> target_waypoints_;

	int iter;

	DynamicFaceDemo();

	void Setup();
	void Update();
	void Exit();
	void Draw();
};

