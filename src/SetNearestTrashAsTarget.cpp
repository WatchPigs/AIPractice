#include "SetNearestTrashAsTarget.h"

SetNearestTrashAsTarget::SetNearestTrashAsTarget(Blackboard* blackboard_jr) :
	Task(blackboard_jr)
{
}

bool SetNearestTrashAsTarget::Run()
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(blackboard_);
	bool result = false;
	if (blackboard_jr == nullptr || blackboard_jr->in_cleaning_up_) return false;
	else
	{
		std::shared_lock<std::shared_mutex> lock_in_use(blackboard_jr->mtx_bb_in_use_);
		std::shared_lock<std::shared_mutex> lock_trashes(blackboard_jr->mtx_trashes_, std::defer_lock);
		std::shared_lock<std::shared_mutex> lock_character_position(blackboard_jr->mtx_character_position_, std::defer_lock);

		std::set<Trash*> trashes;
		glm::vec2 character_position = glm::zero<glm::vec2>();
		while (isThreadRunning())
		{
			if (trashes.size() == 0 && lock_trashes.try_lock())
			{
				trashes = blackboard_jr->trashes_;
				lock_trashes.unlock();
				break;
			}
		}
		while (isThreadRunning())
		{
			if (character_position == glm::zero<glm::vec2>() && lock_character_position.try_lock())
			{
				character_position = blackboard_jr->character_position_;
				lock_character_position.unlock();
				break;
			}
		}
		if (trashes.size() > 0 && character_position != glm::zero<glm::vec2>())
		{
			blackboard_jr->target_ = Nearest(trashes, character_position);
			result = true;
		}
	}
	return result;
}

InteractableObject* SetNearestTrashAsTarget::Nearest(std::set<Trash*> trashes, glm::vec2 character_position)
{
	float nearest_distance = -1.0f;
	Trash* nearest_trash = nullptr;

	for (Trash* trash : trashes)
	{
		float distance = glm::length(trash->rigidbody_->position_ - character_position);
		if (nearest_distance == -1.0f || nearest_distance > distance)
		{
			nearest_distance = distance;
			nearest_trash = trash;
		}
	}
	return nearest_trash;
}
