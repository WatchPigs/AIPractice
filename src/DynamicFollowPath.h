#pragma once
#include "DynamicSeek.h"
#include "DynamicArrive.h"
#include "Path.h"

class DynamicFollowPath : public DynamicSeek
{
public:
	Path* path_;

	// The distance along the path to generate the target. Can be negative if the character is moving in the reverse direction.
	float path_offset_;

	// check how many points ahead for looking for the nearest point;
	int look_ahead_for_nearest_;

	// The current position on the path.
	int current_param_;

	// The target position with offset.
	int target_param_;

	// The minimum distance required for the character on the path
	float path_range_;

	DynamicFollowPath();
	~DynamicFollowPath();
	
	void NewRequest(Rigidbody* character, Path* path, float path_offset, int look_ahead_for_nearest, float path_range, float max_acceleration);

	DynamicSteeringOutput GetSteering() override;
};

