#include "DynamicSeek.h"

DynamicSeek::DynamicSeek() :
	character_rb_(nullptr), target_rb_(nullptr), max_acceleration_(0.0f), arrived_(true)
{
}

DynamicSeek::~DynamicSeek()
{
}

void DynamicSeek::NewRequest(Rigidbody* character, Rigidbody* target, float max_acceleration)
{
	character_rb_ = character;
	target_rb_ = target;
	max_acceleration_ = max_acceleration;
	arrived_ = false;
}

DynamicSteeringOutput DynamicSeek::GetSteering()
{
	DynamicSteeringOutput result;

	// Get the direction to the target.
	result.linear = target_rb_->position_ - character_rb_->position_;

	// Give full acceleration along this direction.
	result.linear = glm::normalize(result.linear);
	result.linear *= max_acceleration_;

	result.angular = 0;

	return result;
}

