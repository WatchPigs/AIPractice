#pragma once
#include "Rigidbody.h"

class KinematicArrive
{
public:

	Rigidbody* character_rb_;
	Rigidbody* target_rb_;

	float max_speed_;

	// The satisfaction radius.
	float radius_;

	// The time to target constant.
	float time_to_target_;

	bool arrived_;

	KinematicArrive();

	void NewRequest(Rigidbody* character, Rigidbody* target, float max_speed, float radius, float time_to_target);

	KinematicSteeringOutput GetSteering();
};

