#include "DynamicArrive.h"

DynamicArrive::DynamicArrive() :
	character_rb_(nullptr), target_rb_(nullptr), max_acceleration_(0.0f), max_speed_(0.0f), target_radius_(0.0f), slow_radius_(0.0f), time_to_target_(0.0f), arrived_(true)
{
}

DynamicArrive::~DynamicArrive()
{
}

void DynamicArrive::NewRequest(Rigidbody* character, Rigidbody* target, float max_acceleration, float max_speed, float target_radius, float slow_radius, float time_to_target)
{
	character_rb_ = character;
	target_rb_ = target;
	max_acceleration_ = max_acceleration;
	max_speed_ = max_speed;
	target_radius_ = target_radius;
	slow_radius_ = slow_radius;
	time_to_target_ = time_to_target;
	arrived_ = false;
}

DynamicSteeringOutput DynamicArrive::GetSteering()
{
	DynamicSteeringOutput result;

	// Get the direction to the target.
	glm::vec2 direction = target_rb_->position_ - character_rb_->position_;
	float distance = glm::length(direction);

	// Check if we are there, return no steering.
	if (distance < target_radius_)
	{
		result.linear = glm::vec2(0.0f, 0.0f);
		result.angular = 0.0f;
		return result;
	}

	float target_speed;
	// If we are outside the slowRadius, then move at max speed.
	if (distance > slow_radius_)
	{
		target_speed = max_speed_;
	}
	// Otherwise calculate a scaled speed.
	else
	{
		target_speed = max_speed_ * distance / slow_radius_;
	}

	// The target velocity combines speed and direction.
	glm::vec2 target_velocity = direction;
	target_velocity = glm::normalize(target_velocity);
	target_velocity *= target_speed;

	// Acceleration tries to get to the target velocity.
	result.linear = target_velocity - character_rb_->velocity_;
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
