#pragma once
#include "Task.h"
#include "BBTest.h"
#include <functional>

class CheckValueTest : public Task
{
public:
	CheckValueTest(Blackboard* bb_test, std::function<bool(int)> checker);
protected:
	std::function<bool(int)> checker_;
	bool Run() override;
};

