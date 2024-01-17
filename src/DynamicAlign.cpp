#include "DynamicAlign.h"

DynamicAlign::DynamicAlign() :
	character_rb_(nullptr), target_rb_(nullptr), max_angular_acceleration_(0.0f), max_rotation_(0.0f), target_radius_(0.0f), slow_radius_(0.0f), time_to_target_(0.0f), arrived_(true)
{
}

DynamicAlign::~DynamicAlign()
{
}

void DynamicAlign::NewRequest(Rigidbody* character, Rigidbody* target, float max_angular_acceleration, float max_rotation, float target_radius, float slow_radius, float time_to_target)
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

DynamicSteeringOutput DynamicAlign::GetSteering()
{
	DynamicSteeringOutput result;

	// Get the naive direction to the target.
	float rotation = target_rb_->orientation_ - character_rb_->orientation_;

	// Map the result to the (-pi, pi) interval.
	rotation = ofWrapRadians(rotation, -glm::pi<float>(), glm::pi<float>());
	float rotation_size = abs(rotation);

	// Check if we are there, return no steering.
	if (rotation_size < target_radius_)
	{
		result.linear = glm::vec2(0.0f, 0.0f);
		result.angular = 0.0f;
		return result;
	}

	float target_rotation;
	// If we are outside the slowRadius, then use maximum rotation.
	if (rotation_size > slow_radius_)
	{
		target_rotation = max_rotation_;
	}
	// Otherwise calculate a scaled rotation.
	else
	{
		target_rotation = max_rotation_ * rotation_size / slow_radius_;
	}

	// The final target rotation combines speed (already in the variable) and direction.
	target_rotation *= rotation / rotation_size;

	// Acceleration tries to get to the target rotation.
	result.angular = target_rotation - character_rb_->rotation_;
	result.angular /= time_to_target_;

	// Check if the acceleration is too great.
	float angular_acceleration = abs(result.angular);
	if (angular_acceleration > max_angular_acceleration_)
	{
		result.angular /= angular_acceleration;
		result.angular *= max_angular_acceleration_;
	}
	result.linear = glm::zero<glm::vec2>();
	return result;
}
