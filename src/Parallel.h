#pragma once
#include "Task.h"
#include <set>

class Parallel : public Task
{
public:
	std::vector<Task*> children_;

	void AddChild(Task* child);

protected:
	bool Run() override;
	// Holds all the children currently running.
	std::set<Task*> running_children_;
};

