#include "DynamicSeparation.h"

DynamicSeparation::DynamicSeparation() :
	character_rb_(nullptr), max_acceleration_(0.0f), threshold_(0.0f), decay_coefficient_(0.0f), arrived_(true)
{
}

void DynamicSeparation::NewRequest(Rigidbody* character, std::vector<Rigidbody*> targets, float threshold, float decay_coefficient, float max_acceleration)
{
	character_rb_ = character;
	targets_ = targets;
	threshold_ = threshold;
	decay_coefficient_ = decay_coefficient;
	max_acceleration_ = max_acceleration;
	arrived_ = false;
}

DynamicSteeringOutput DynamicSeparation::GetSteering()
{
	DynamicSteeringOutput result;

	// Loop through each target.
	for (Rigidbody* target : targets_)
	{
		// Check if the target is close.
		glm::vec2 direction = target->position_ - character_rb_->position_;
		float distance = glm::length(direction);

		if (distance < threshold_)
		{
			// Calculate the strength of repulsion (here using the inverse square law).
			float strength = min(decay_coefficient_ / (distance * distance), max_acceleration_);

			// Add the acceleration.
			result.linear += strength * glm::normalize(direction);
		}
	}
	return result;
}

