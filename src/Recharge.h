#pragma once
#include "Task.h"
#include "BlackboardJR.h"

class Recharge : public Task
{
public:
	int duration_;
	int max_terminate_time_;

	Recharge(Blackboard* blackboard_jr, int duration, int max_terminate_time);
	Recharge() = delete;

protected:
	bool Run() override;
};

