#include "DynamicFollowPath.h"

DynamicFollowPath::DynamicFollowPath() :
	DynamicSeek(), path_(nullptr), path_offset_(0.0f), look_ahead_for_nearest_(0), current_param_(-1), path_range_(0.0f)
{
	target_rb_ = new Rigidbody();
}

DynamicFollowPath::~DynamicFollowPath()
{
	if (target_rb_ != nullptr)
	{
		delete target_rb_;
		target_rb_ == nullptr;
	}
}

void DynamicFollowPath::NewRequest(Rigidbody* character, Path* path, float path_offset, int look_ahead_for_nearest, float path_range, float max_acceleration)
{
	character_rb_ = character;
	path_ = path;
	path_offset_ = path_offset;
	look_ahead_for_nearest_ = look_ahead_for_nearest;
	current_param_ = -1;
	path_range_ = path_range;
	max_acceleration_ = max_acceleration;
	arrived_ = false;
}

DynamicSteeringOutput DynamicFollowPath::GetSteering()
{
	// Find the current position on the path.
	if (current_param_ == -1) current_param_ = path_->GetNearestPointParam(character_rb_->position_, true);
	else current_param_ = path_->GetNearestPointParam(character_rb_->position_, false, current_param_, look_ahead_for_nearest_);

	// If character is too far away from current nearest position, target position is current nearest position, else get the target position with offset
	target_param_ = glm::length(path_->GetPosition(current_param_) - character_rb_->position_) > path_range_ ? current_param_ : path_->GetTargetPointParamWithOffset(current_param_, path_offset_);

	// Get the target position.
	target_rb_->position_ = path_->GetPosition(target_param_);

	// Delegate to seek.
	return DynamicSeek::GetSteering();
}
