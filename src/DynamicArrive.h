#pragma once
#include <atomic>
#include "Rigidbody.h"

class DynamicArrive
{
public:
	Rigidbody* character_rb_;
	Rigidbody* target_rb_;

	float max_acceleration_;
	float max_speed_;

	// The radius for arriving at the target.
	float target_radius_;

	// The radius for beginning to slow down.
	float slow_radius_;

	// The time over which to achieve target speed.
	float time_to_target_;

	// set arrived when it reaches the target radius and has the speed lower than this
	float arrived_speed_;

	std::atomic<bool> arrived_;

	DynamicArrive();
	virtual ~DynamicArrive();

	void NewRequest(Rigidbody* character, Rigidbody* target, float max_acceleration, float max_speed, float target_radius, float slow_radius, float time_to_target, float arrived_speed = -1.0f);

	DynamicSteeringOutput GetSteering();
};

