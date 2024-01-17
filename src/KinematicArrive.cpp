#include "KinematicArrive.h"

KinematicArrive::KinematicArrive() :
	character_rb_(nullptr), target_rb_(nullptr), max_speed_(0.0f), radius_(0.0f), time_to_target_(0.0f), arrived_(true)
{
}

void KinematicArrive::NewRequest(Rigidbody* character, Rigidbody* target, float max_speed, float radius, float time_to_target)
{
	character_rb_ = character;
	target_rb_ = target;
	max_speed_ = max_speed;
	radius_ = radius;
	time_to_target_ = time_to_target;
	arrived_ = false;
}

KinematicSteeringOutput KinematicArrive::GetSteering()
{
	KinematicSteeringOutput	result;

	// Get the direction to the target.
	result.velocity = target_rb_->position_ - character_rb_->position_;

	// Check if we are within radius.
	if (glm::length(result.velocity) < radius_)
	{
		// Request no steering.
		arrived_ = true;
		result.velocity = glm::vec2(0.0f, 0.0f);
		result.rotation = 0.0f;
		return result;
	}

	// We need to move to our target, we would like to get there in timeToTarget seconds.
	result.velocity /= time_to_target_;

	// If this is too fast, clip it to the max speed.
	if (glm::length(result.velocity) > max_speed_)
	{
		result.velocity = glm::normalize(result.velocity);
		result.velocity *= max_speed_;
	}

	result.rotation = 0.0f;

	return result;
}
