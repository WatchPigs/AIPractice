#pragma once
#include "Task.h"
#include "BBTest.h"

class LogValueTest : public Task
{
public:
	LogValueTest(Blackboard* bb_test);
protected:
	bool Run() override;
};

