#pragma once
#include "Task.h"
#include "BlackboardJR.h"

class DetectSufficientPower : public Task
{
public:
	DetectSufficientPower(Blackboard* blackboard_jr);
	DetectSufficientPower() = delete;

protected:
	bool Run() override;
};

