#pragma once
#include "Task.h"
#include "BBTest.h"
#include <functional>

class IncrementTest : public Task
{
public:
	IncrementTest(BBTest* bb_test);

protected:
	bool Run() override;
};

