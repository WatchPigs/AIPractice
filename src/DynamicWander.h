#pragma once
#include "Rigidbody.h"
#include "DynamicFace.h"

class DynamicWander : public DynamicFace
{
public:
	// The radius and forward offset of the wander circle.
	float wander_offset_;
	float wander_radius_;

	// The maximum rate at which the wander orientation can change
	float wander_rate_;

	// The current orientation of the wander target.
	float wander_orientation_;

	// The maximum acceleration of the character.
	float max_acceleration_;

	// The circle center for drawing;
	glm::vec2 circle_position_;

	DynamicWander();
	virtual ~DynamicWander();

	void NewRequest(Rigidbody* character, float wander_offset, float wander_radius, float wander_rate, float max_acceleration, float max_angular_acceleration, float max_rotation, float target_radius, float slow_radius, float time_to_target);

	DynamicSteeringOutput GetSteering() override;
};

