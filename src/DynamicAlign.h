#pragma once
#include "Rigidbody.h"

class DynamicAlign
{
public:
	Rigidbody* character_rb_;
	Rigidbody* target_rb_;

	float max_angular_acceleration_;
	float max_rotation_;

	// The radius for arriving at the target.
	float target_radius_;

	// The radius for beginning to slow down.
	float slow_radius_;

	// The time over which to achieve target speed.
	float time_to_target_;

	bool arrived_;

	DynamicAlign();
	virtual ~DynamicAlign();

	virtual void NewRequest(Rigidbody* character, Rigidbody* target, float max_angular_acceleration, float max_rotation, float target_radius, float slow_radius, float time_to_target);

	virtual DynamicSteeringOutput GetSteering();
};

