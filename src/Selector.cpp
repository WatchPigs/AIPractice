#include "Selector.h"

bool Selector::Run()
{
	if (children_.size() == 0) return false;
	for (Task* child : children_)
	{
		if (!isThreadRunning()) return false;
		running_task_ = child;

		child->startThread();
		child->waitForThread(false);
		if (child->result_) return true;
	}
	running_task_ = nullptr;
	return false;
}

Selector::Selector() :
	running_task_(nullptr)
{
}

void Selector::AddChild(Task* child)
{
	children_.push_back(child);
}

void Selector::Terminate()
{
	stopThread();
	if (running_task_ != nullptr)
	{
		running_task_->Terminate();
		running_task_ = nullptr;
	}
}
