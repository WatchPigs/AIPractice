#include "DynamicObstacleAvoidance.h"

DynamicObstacleAvoidance::DynamicObstacleAvoidance() :
	DynamicSeek(), detector_(nullptr), avoid_distance_(0.0f), lookahead_(0.0f)
{
	target_rb_ = new Rigidbody();
}

DynamicObstacleAvoidance::~DynamicObstacleAvoidance()
{
	if (target_rb_ != nullptr)
	{
		delete target_rb_;
		target_rb_ = nullptr;
	}
}

void DynamicObstacleAvoidance::NewRequest(Rigidbody* character, CollisionDetector* detector, float avoid_distance, float lookahead, float max_acceleration)
{
	character_rb_ = character;
	detector_ = detector;
	avoid_distance_ = avoid_distance;
	lookahead_ = lookahead;
	max_acceleration_ = max_acceleration;
	arrived_ = false;
}

DynamicSteeringOutput DynamicObstacleAvoidance::GetSteering()
{
	// Calculate the collision ray vector.
	glm::vec2 ray = character_rb_->velocity_;
	ray = glm::normalize(ray);
	ray *= lookahead_;

	draw_ray_ = ray;

	// Find the collision
	auto collision = detector_->GetCollision(character_rb_->position_, ray);

	// If have no collision, do nothing.
	if (!collision.collided)
	{
		DynamicSteeringOutput result;
		result.linear = glm::vec2(0.0f, 0.0f);
		result.angular = 0.0f;
		return result;
	}

	// Otherwise create a target and delegate to seek.
	target_rb_->position_ = collision.position + collision.normal * avoid_distance_;

	return DynamicSeek::GetSteering();
}

