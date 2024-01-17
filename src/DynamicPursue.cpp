#include "DynamicPursue.h"

DynamicPursue::DynamicPursue() : 
	DynamicSeek(), target_rb_(nullptr), max_prediction_(0.0f)
{
	DynamicSeek::target_rb_ = new Rigidbody();
}

DynamicPursue::~DynamicPursue()
{
	if (DynamicSeek::target_rb_ != nullptr)
	{
		delete DynamicSeek::target_rb_;
		DynamicSeek::target_rb_ = nullptr;
	}
}

void DynamicPursue::NewRequest(Rigidbody* character, Rigidbody* target, float max_acceleration, float max_prediction)
{
	character_rb_ = character;
	target_rb_ = target;
	max_acceleration_ = max_acceleration;
	max_prediction_ = max_prediction;
	arrived_ = false;
}

DynamicSteeringOutput DynamicPursue::GetSteering()
{
	// Calculate the target to delegate to seek
	// Work out the distance to target.
	glm::vec2 direction = target_rb_->position_ - character_rb_->position_;
	float distance = glm::length(direction);

	// Work out our current speed.
	float speed = glm::length(character_rb_->velocity_);

	// Check if speed gives a reasonable prediction time.
	float prediction;
	if (speed <= distance / max_prediction_)
	{
		prediction = max_prediction_;
	}
	else
	{
		prediction = distance / speed;
	}

	// predict the position.
	DynamicSeek::target_rb_->position_ = target_rb_->position_ + target_rb_->velocity_ * prediction;

	return DynamicSeek::GetSteering();
}
