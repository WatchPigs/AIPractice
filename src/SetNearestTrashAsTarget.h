#pragma once
#include "Task.h"
#include "BlackboardJR.h"

class SetNearestTrashAsTarget : public Task
{
public:
	SetNearestTrashAsTarget(Blackboard* blackboard_jr);
	SetNearestTrashAsTarget() = delete;

protected:
	bool Run() override;

private:
	InteractableObject* Nearest(std::set<Trash*> trashes, glm::vec2 character_position);
};

