#pragma once
#include "Rigidbody.h"
#include "DynamicAlign.h"

class DynamicLookWhereYoureGoing : public DynamicAlign
{
public:
	DynamicLookWhereYoureGoing();
	~DynamicLookWhereYoureGoing();

	//void NewRequest(Rigidbody* character, Rigidbody* target, float max_angular_acceleration, float max_rotation, float target_radius, float slow_radius, float time_to_target) = delete;
	void NewRequest(Rigidbody* character, float max_angular_acceleration, float max_rotation, float target_radius, float slow_radius, float time_to_target);

	DynamicSteeringOutput GetSteering() override;
};

