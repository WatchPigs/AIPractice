#include "Parallel.h"

bool Parallel::Run()
{
	if (children_.size() == 0) return false;
	for (Task* child : children_)
	{
		if (!isThreadRunning())
		{
			for (Task* running_child : running_children_) running_child->Terminate();
			for (Task* running_child : running_children_) running_child->waitForThread(false);
			running_children_.clear();
			return false;
		}
		child->startThread();
		running_children_.insert(child);
	}

	bool temp_result = true;
	while (temp_result)
	{
		for (std::set<Task*>::iterator running_children_it = running_children_.begin(); running_children_it != running_children_.end();)
		{
			if (!isThreadRunning())
			{
				for (Task* running_child : running_children_) running_child->Terminate();
				for (Task* running_child : running_children_) running_child->waitForThread(false);
				running_children_.clear();
				return false;
			}
			if ((*running_children_it)->isThreadDone())
			{
				Task* running_child = *running_children_it;
				running_children_.erase(running_children_it++);
				if (!running_child->result_)
				{
					temp_result = false;
					for (Task* remain_running_child : running_children_) remain_running_child->Terminate();
					for (Task* remain_running_child : running_children_) remain_running_child->waitForThread(false);
					running_children_.clear();
					break;
				}
			}
			else running_children_it++;
		}
		if (running_children_.size() == 0) break;
	}

	return temp_result;
}

void Parallel::AddChild(Task* child)
{
	children_.push_back(child);
}

