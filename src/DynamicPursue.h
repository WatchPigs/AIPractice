#pragma once
#include "DynamicSeek.h"

class DynamicPursue : public DynamicSeek
{
public:
	
	// This is the target we are pursuing, and DynamicSeek::target_rb_ in the superclass is used as the predicted target location.
	Rigidbody* target_rb_;

	// The maximum prediction time.
	float max_prediction_;

	DynamicPursue();
	~DynamicPursue();

	void NewRequest(Rigidbody* character, Rigidbody* target, float max_acceleration, float max_prediction);

	DynamicSteeringOutput GetSteering() override;
};

