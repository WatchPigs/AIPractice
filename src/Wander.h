#pragma once
#include "Task.h"
#include "BlackboardJR.h"
#include "DynamicWander.h"

// This will never end or return true, it can only be terminated
class Wander : public Task
{
public:
	DynamicWander* dynamic_wander_;

	Wander(Blackboard* blackboard_jr);
	Wander() = delete;
	~Wander();

protected:
	bool Run() override;
};

