#pragma once
#include "Rigidbody.h"
#include <vector>

class DynamicSeparation
{
public:
	Rigidbody* character_rb_;

	// A list of potential targets
	std::vector<Rigidbody*> targets_;

	// The threshold to take action.
	float threshold_;

	// The constant coefficient of decay for the inverse square law.
	float decay_coefficient_;

	float max_acceleration_;

	bool arrived_;

	DynamicSeparation();

	void NewRequest(Rigidbody* character, std::vector<Rigidbody*> targets, float threshold, float decay_coefficient, float max_acceleration);

	DynamicSteeringOutput GetSteering();
};

