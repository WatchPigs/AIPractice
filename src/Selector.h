#pragma once
#include "Task.h"
#include <vector>

class Selector : public Task
{
public:
	std::vector<Task*> children_;

	Selector();
	void AddChild(Task* child);
	void Terminate() override;

protected:
	bool Run() override;
	Task* running_task_;
};

