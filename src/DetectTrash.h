#pragma once
#include "Task.h"
#include "BlackboardJR.h"

class DetectTrash : public Task
{
public:
	DetectTrash(Blackboard* blackboard_jr);
	DetectTrash() = delete;

protected:
	bool Run() override;
};

