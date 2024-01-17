#include "DynamicWander.h"
#include "Utils.h"

DynamicWander::DynamicWander() :
DynamicFace(), wander_offset_(0.0f), wander_radius_(0.0f), wander_rate_(0.0f), wander_orientation_(0.0f), max_acceleration_(0.0f), circle_position_(glm::zero<glm::vec2>())
{
	target_rb_ = new Rigidbody();
}

DynamicWander::~DynamicWander()
{
	if (target_rb_ != nullptr)
	{
		delete target_rb_;
		target_rb_ = nullptr;
	}
}

void DynamicWander::NewRequest(Rigidbody* character, float wander_offset, float wander_radius, float wander_rate, float max_acceleration, float max_angular_acceleration, float max_rotation, float target_radius, float slow_radius, float time_to_target)
{
	character_rb_ = character;
	wander_offset_ = wander_offset;
	wander_radius_ = wander_radius;
	wander_rate_ = wander_rate;
	wander_orientation_ = 0.0f;
	max_acceleration_ =	max_acceleration;
	max_angular_acceleration_ = max_angular_acceleration;
	max_rotation_ = max_rotation;
	target_radius_ = target_radius;
	slow_radius_ = slow_radius;
	time_to_target_ = time_to_target;
	arrived_ = false;
}

DynamicSteeringOutput DynamicWander::GetSteering()
{
	// Update the wander orientation.
	wander_orientation_ += RandomBinomial() * wander_rate_;

	// Calculate the combined target orientation.
	float target_orientation = wander_orientation_ + character_rb_->orientation_;

	// Calculate the center of the wander circle.
	target_rb_->position_ = character_rb_->position_ + wander_offset_ * AsVector(character_rb_->orientation_);

	circle_position_ = target_rb_->position_;

	// Calculate the target location.
	target_rb_->position_ += wander_radius_ * AsVector(target_orientation);

	// Delegate to DynamicFace.
	DynamicSteeringOutput result = DynamicFace::GetSteering();

	// Acceleration in the direction of the orientation
	result.linear = max_acceleration_ * AsVector(character_rb_->orientation_);

	return result;
}

