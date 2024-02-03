#pragma once
#include "Task.h"
#include "BlackboardJR.h"

class TidyTrash : public Task
{
public:
	int duration_;
	int max_terminate_time_;

	TidyTrash(Blackboard* blackboard_jr, int duration, int max_terminate_time);
	TidyTrash() = delete;

protected:
	bool Run() override;

};

