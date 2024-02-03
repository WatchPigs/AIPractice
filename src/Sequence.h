#pragma once
#include "Task.h"
#include <vector>

class Sequence : public Task
{
public:
	std::vector<Task*> children_;

	Sequence();
	void AddChild(Task* child);
	void Terminate() override;

protected:
	bool Run() override;
	Task* running_task_;
};

