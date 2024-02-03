#include "KinematicStop.h"

KinematicStop::KinematicStop() :
	character_rb_(nullptr), arrived_(true)
{
}

void KinematicStop::NewRequest(Rigidbody* character)
{
	character_rb_ = character;
	arrived_ = false;
}

KinematicSteeringOutput KinematicStop::GetSteering()
{
	KinematicSteeringOutput	result;

	result.velocity = glm::zero<glm::vec2>();
	result.rotation = 0.0f;

	arrived_ = true;

	return result;
}

