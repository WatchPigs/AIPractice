#pragma once
#include "Task.h"

// This is still an abstract class without implementing function Run()
class Decorator : public Task
{
public:
	// Stores the child this task is decorating.
	Task* child_;

	Decorator();
	void SetChild(Task* child);
	void Terminate() override;
};

