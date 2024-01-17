#pragma once
#include "Rigidbody.h"
#include "DynamicSeek.h"
#include "CollisionDetector.h"

class DynamicObstacleAvoidance : public DynamicSeek
{
public:
	
	CollisionDetector* detector_;
	// The minimum distance to a wall (i.e., how far to avoid
	float avoid_distance_;

	// The distance to look ahead for a collision (i.e., the length of the collision ray)
	float lookahead_;

	glm::vec2 draw_ray_;

	DynamicObstacleAvoidance();
	~DynamicObstacleAvoidance();

	void NewRequest(Rigidbody* character, CollisionDetector* detector, float avoid_distance, float lookahead, float max_acceleration);

	DynamicSteeringOutput GetSteering() override;
};

