#pragma once
#include "ofMain.h"
#include "KinematicSteeringOutput.h"
#include "DynamicSteeringOutput.h"

class Rigidbody
{
public:
	glm::vec2 position_;
	float orientation_;

	glm::vec2 velocity_;
	float rotation_;

	float mass_;

	Rigidbody();
	Rigidbody(glm::vec2 position, float orientation, glm::vec2 velocity, float rotation, float mass = 1.0f);
	~Rigidbody();

	void Rigidbody::update(float time);
	void update(KinematicSteeringOutput steering, float time);
	void update(DynamicSteeringOutput steering, float max_speed, float time);
};

