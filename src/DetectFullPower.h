#pragma once
#include "Task.h"
#include "BlackboardJR.h"

class DetectFullPower : public Task
{
public:
	DetectFullPower(Blackboard* blackboard_jr);
	DetectFullPower() = delete;

protected:
	bool Run() override;
};

