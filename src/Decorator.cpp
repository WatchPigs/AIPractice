#include "Decorator.h"

Decorator::Decorator() :
	child_(nullptr)
{
}

void Decorator::SetChild(Task* child)
{
	child_ = child;
}

void Decorator::Terminate()
{
	stopThread();
	if (child_->isThreadRunning())
	{
		child_->Terminate();
	}
}
