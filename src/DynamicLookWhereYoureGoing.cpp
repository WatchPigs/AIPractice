#include "DynamicLookWhereYoureGoing.h"

DynamicLookWhereYoureGoing::DynamicLookWhereYoureGoing() :
	DynamicAlign()
{
	DynamicAlign::target_rb_ = new Rigidbody();
}

DynamicLookWhereYoureGoing::~DynamicLookWhereYoureGoing()
{
	if (DynamicAlign::target_rb_ != nullptr)
	{
		delete DynamicAlign::target_rb_;
		DynamicAlign::target_rb_ = nullptr;
	}
}

void DynamicLookWhereYoureGoing::NewRequest(Rigidbody* character, float max_angular_acceleration, float max_rotation, float target_radius, float slow_radius, float time_to_target)
{
	character_rb_ = character;
	max_angular_acceleration_ = max_angular_acceleration;
	max_rotation_ = max_rotation;
	target_radius_ = target_radius;
	slow_radius_ = slow_radius;
	time_to_target_ = time_to_target;
	arrived_ = false;
}

DynamicSteeringOutput DynamicLookWhereYoureGoing::GetSteering()
{
	// Calculate the target to delegate to align
	// Check for a zero direction, and make no change if so.
	glm::vec2 velocity = character_rb_->velocity_;
	if (glm::length(velocity) == 0)
	{
		DynamicSteeringOutput result;
		result.linear = glm::vec2(0.0f, 0.0f);
		result.angular = 0.0f;
		return result;
	}

	// Otherwise set the target based on the velocity.
	DynamicAlign::target_rb_->orientation_ = atan2(velocity.y, velocity.x);

	// Delegate to align.
	return DynamicAlign::GetSteering();
}
