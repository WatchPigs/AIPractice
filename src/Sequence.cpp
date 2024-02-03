#include "Sequence.h"

bool Sequence::Run()
{
	if (children_.size() == 0) return false;
	for (Task* child : children_)
	{
		if (!isThreadRunning()) return false;
		running_task_ = child;

		child->startThread();
		child->waitForThread(false);
		if (!child->result_) return false;
	}
	running_task_ = nullptr;
	return true;
}

Sequence::Sequence() :
	running_task_(nullptr)
{
}

void Sequence::AddChild(Task* child)
{
	children_.push_back(child);
}

void Sequence::Terminate()
{
	stopThread();
	if (running_task_ != nullptr)
	{
		running_task_->Terminate();
		running_task_ = nullptr;
	}
}
