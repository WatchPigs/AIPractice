#pragma once
#include "Rigidbody.h"
#include "DynamicAlign.h"

class DynamicFace : public DynamicAlign
{
public:
	// This is the target we are facing, and the target in the superclass is used to set the orientation to align.
	Rigidbody* target_rb_;

	DynamicFace();
	virtual ~DynamicFace();

	void NewRequest(Rigidbody* character, Rigidbody* target, float max_angular_acceleration, float max_rotation, float target_radius, float slow_radius, float time_to_target) override;

	// Implemented as it was in Pursue.
	DynamicSteeringOutput GetSteering() override;
};

