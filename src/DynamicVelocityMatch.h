#pragma once
#include "Rigidbody.h"

class DynamicVelocityMatch
{
public:
	Rigidbody* character_rb_;
	Rigidbody* target_rb_;

	float max_acceleration_;

	float time_to_target_;

	bool arrived_;

	DynamicVelocityMatch();

	void NewRequest(Rigidbody* character, Rigidbody* target, float max_acceleration, float time_to_target);

	DynamicSteeringOutput GetSteering();
};

