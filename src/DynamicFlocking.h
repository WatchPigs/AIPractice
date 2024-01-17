#pragma once
#include "Rigidbody.h"
#include <vector>
#include "DynamicSeparation.h"
#include "DynamicAlign.h"
#include "DynamicVelocityMatch.h"
#include "DynamicArrive.h"

class DynamicFlocking
{
public:
	Rigidbody* character_rb_;
	std::vector<Rigidbody*> targets_;
	Rigidbody* centroid_rb_;

	// Weighted blended steering of four steering behaviors
	DynamicSeparation* dynamic_separation_;
	DynamicAlign* dynamic_align_;
	DynamicVelocityMatch* dynamic_velocity_match_;
	DynamicArrive* dynamic_arrive_;

	float dynamic_separation_weight_;
	float dynamic_align_weight_;
	float dynamic_velocity_match_weight_;
	float dynamic_arrive_weight_;

	float max_acceleration_;
	float max_angular_acceleration_;

	bool arrived_;

	DynamicFlocking();
	~DynamicFlocking();

	void DynamicFlocking::NewRequest(Rigidbody* character, std::vector<Rigidbody*> targets,
		float separation_threshold, float separation_decay_coefficient, float separation_max_acceleration,
		float align_max_angular_acceleration, float align_max_rotation, float align_target_radius, float align_slow_radius, float align_time_to_target,
		float velocity_match_max_acceleration, float velocity_match_time_to_target,
		float arrive_max_acceleration, float arrive_max_speed, float arrive_target_radius, float arrive_slow_radius, float arrive_time_to_target,
		float dynamic_separation_weight, float dynamic_align_weight, float dynamic_velocity_match_weight, float dynamic_arrive_weight,
		float max_acceleration, float max_angular_acceleration);

	DynamicSteeringOutput GetSteering();
};

