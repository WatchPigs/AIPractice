#include "Rigidbody.h"
#include "Utils.h"

Rigidbody::Rigidbody() :
	position_(glm::vec2(0.0f, 0.0f)), orientation_(0.0f), velocity_(glm::vec2(0.0f, 0.0f)), rotation_(0.0f), mass_(1.0f)
{}

Rigidbody::Rigidbody(glm::vec2 position, float orientation, glm::vec2 velocity, float rotation, float mass) :
	position_(position), orientation_(orientation), velocity_(velocity), rotation_(rotation), mass_(mass)
{}

Rigidbody::~Rigidbody()
{}

void Rigidbody::update(float time)
{
	// Update the position and orientation.
	position_ += velocity_ * time;
	orientation_ += rotation_ * time;
}

void Rigidbody::update(KinematicSteeringOutput steering, float time)
{
	// Update the position and orientation.
	position_ += velocity_ * time;
	orientation_ += rotation_ * time;

	// and the velocity and rotation.
	velocity_ = steering.velocity;
	rotation_ = steering.rotation;
}

void Rigidbody::update(DynamicSteeringOutput steering, float max_speed, float time)
{
	// Update the position and orientation.
	position_ += velocity_ * time;
	orientation_ += rotation_ * time;

	// and the velocity and rotation.
	velocity_ += steering.linear * time;
	rotation_ += steering.angular * time;

	// Check for speeding and clip.
	if (glm::length(velocity_) > max_speed)
	{
		velocity_ = glm::normalize(velocity_);
		velocity_ *= max_speed;
	}
}
