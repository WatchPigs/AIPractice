#include "DynamicFlocking.h"

DynamicFlocking::DynamicFlocking() :
	character_rb_(nullptr), centroid_rb_(nullptr), dynamic_separation_weight_(0.0f), dynamic_align_weight_(0.0f), dynamic_velocity_match_weight_(0.0f), dynamic_arrive_weight_(0.0f), max_acceleration_(0.0f), max_angular_acceleration_(0.0f), arrived_(true)
{
	centroid_rb_ = new Rigidbody();
	dynamic_separation_ = new DynamicSeparation();
	dynamic_align_ = new DynamicAlign();
	dynamic_velocity_match_ = new DynamicVelocityMatch();
	dynamic_arrive_ = new DynamicArrive();
}

DynamicFlocking::~DynamicFlocking()
{
	if (centroid_rb_ != nullptr)
	{
		delete centroid_rb_;
		centroid_rb_ = nullptr;
	}
	if (dynamic_separation_ != nullptr)
	{
		delete dynamic_separation_;
		dynamic_separation_ = nullptr;
	}
	if (dynamic_align_ != nullptr)
	{
		delete dynamic_align_;
		dynamic_align_ = nullptr;
	}
	if (dynamic_velocity_match_ != nullptr)
	{
		delete dynamic_velocity_match_;
		dynamic_velocity_match_ = nullptr;
	}
	if (dynamic_arrive_ != nullptr)
	{
		delete dynamic_arrive_;
		dynamic_arrive_ = nullptr;
	}
}

void DynamicFlocking::NewRequest(Rigidbody* character, std::vector<Rigidbody*> targets, 
	float separation_threshold, float separation_decay_coefficient, float separation_max_acceleration,
	float align_max_angular_acceleration, float align_max_rotation, float align_target_radius, float align_slow_radius, float align_time_to_target,
	float velocity_match_max_acceleration, float velocity_match_time_to_target,
	float arrive_max_acceleration, float arrive_max_speed, float arrive_target_radius, float arrive_slow_radius, float arrive_time_to_target,
	float dynamic_separation_weight, float dynamic_align_weight, float dynamic_velocity_match_weight, float dynamic_arrive_weight, 
	float max_acceleration, float max_angular_acceleration)
{
	character_rb_ = character;
	targets_ = targets;

	dynamic_separation_->NewRequest(character_rb_, targets_, separation_threshold, separation_decay_coefficient, separation_max_acceleration);
	dynamic_align_->NewRequest(character_rb_, centroid_rb_, align_max_angular_acceleration, align_max_rotation, align_target_radius, align_slow_radius, align_time_to_target);
	dynamic_velocity_match_->NewRequest(character_rb_, centroid_rb_, velocity_match_max_acceleration, velocity_match_time_to_target);
	dynamic_arrive_->NewRequest(character_rb_, centroid_rb_, arrive_max_acceleration, arrive_max_speed, arrive_target_radius, arrive_slow_radius, arrive_time_to_target);

	dynamic_separation_weight_ = dynamic_separation_weight;
	dynamic_align_weight_ = dynamic_arrive_weight;
	dynamic_velocity_match_weight_ = dynamic_velocity_match_weight;
	dynamic_arrive_weight_ = dynamic_arrive_weight;
	max_acceleration_ = max_acceleration;
	max_angular_acceleration_ = max_angular_acceleration;
	arrived_ = false;
}

DynamicSteeringOutput DynamicFlocking::GetSteering()
{
	// Update the centroid of all the targets
	glm::vec2 position_sum = glm::zero<glm::vec2>();
	float orientation_sum = 0.0f;
	glm::vec2 velocity_sum = glm::zero<glm::vec2>();
	float mass_sum = 0.0f;
	for (Rigidbody* target : targets_)
	{
		position_sum += target->position_ * target->mass_;
		orientation_sum += target->orientation_ * target->mass_;
		velocity_sum += target->velocity_ * target->mass_;
		mass_sum += target->mass_;
	}
	centroid_rb_->position_ = position_sum / mass_sum;
	centroid_rb_->orientation_ = orientation_sum / mass_sum;
	centroid_rb_->velocity_ = velocity_sum / mass_sum;

	// Weighted blended steering of four steering behaviors
	return (dynamic_separation_->GetSteering() * dynamic_separation_weight_ + dynamic_align_->GetSteering() * dynamic_align_weight_ + dynamic_velocity_match_->GetSteering() * dynamic_velocity_match_weight_ + dynamic_arrive_->GetSteering() * dynamic_arrive_weight_)
		/ (dynamic_separation_weight_ + dynamic_align_weight_ + dynamic_velocity_match_weight_ + dynamic_arrive_weight_);

}
