#include "DynamicFace.h"

DynamicFace::DynamicFace() :
	DynamicAlign(), target_rb_(nullptr)
{
	DynamicAlign::target_rb_ = new Rigidbody();
}

DynamicFace::~DynamicFace()
{
	if (DynamicAlign::target_rb_ != nullptr)
	{
		delete DynamicAlign::target_rb_;
		DynamicAlign::target_rb_ = nullptr;
	}
}

void DynamicFace::NewRequest(Rigidbody* character, Rigidbody* target, float max_angular_acceleration, float max_rotation, float target_radius, float slow_radius, float time_to_target)
{
	character_rb_ = character;
	target_rb_ = target;
	max_angular_acceleration_ = max_angular_acceleration;
	max_rotation_ = max_rotation;
	target_radius_ = target_radius;
	slow_radius_ = slow_radius;
	time_to_target_ = time_to_target;
	arrived_ = false;
}

DynamicSteeringOutput DynamicFace::GetSteering()
{
	// Calculate the target to delegate to align
	// Work out the direction to target.
	glm::vec2 direction = target_rb_->position_ - character_rb_->position_;

	// Check for a zero direction, and make no change if so.
	if (glm::length(direction) < 0.01f)
	{
		DynamicSteeringOutput result;
		result.linear = glm::vec2(0.0f, 0.0f);
		result.angular = 0.0f;
		return result;
	}

	// Delegate to align.
	DynamicAlign::target_rb_->orientation_ = atan2(direction.y, direction.x);

	return DynamicAlign::GetSteering();
}

