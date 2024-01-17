#include "DynamicVelocityMatch.h"

DynamicVelocityMatch::DynamicVelocityMatch() :
	character_rb_(nullptr), target_rb_(nullptr), max_acceleration_(0.0f), time_to_target_(0.0f), arrived_(true)
{
}

void DynamicVelocityMatch::NewRequest(Rigidbody* character, Rigidbody* target, float max_acceleration, float time_to_target)
{
	character_rb_ = character;
	target_rb_ = target;
	max_acceleration_ = max_acceleration;
	time_to_target_ = time_to_target;
	arrived_ = false;
}

DynamicSteeringOutput DynamicVelocityMatch::GetSteering()
{
	DynamicSteeringOutput result;

	// Acceleration tries to get to the target velocity.
	result.linear = target_rb_->velocity_ - character_rb_->velocity_;
	result.linear /= time_to_target_;

	// Check if the acceleration is too fast.
	if (glm::length(result.linear) > max_acceleration_)
	{
		result.linear = glm::normalize(result.linear);
		result.linear *= max_acceleration_;
	}

	result.angular = 0;
	return result;
}

