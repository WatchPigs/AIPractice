#include "BehaviorTree.h"
#include "ofLog.h"

BehaviorTree::BehaviorTree() :
	blackboard_(nullptr), root_(nullptr), running(false)
{
}

BehaviorTree::~BehaviorTree()
{
}

void BehaviorTree::SafeCleanUp()
{
	TerminateBT();
	waitForThread(false);
	if (all_tasks_.size() > 0)
	{
		for (Task* task : all_tasks_) task->SafeCleanUp();
		for (Task* task : all_tasks_) delete task;
		all_tasks_.clear();
	}
	if (blackboard_ != nullptr)
	{
		blackboard_->SafeCleanUp();
		delete blackboard_;
		blackboard_ = nullptr;
	}
	root_ = nullptr;

	const std::type_info& type2 = typeid(*this);
}

void BehaviorTree::RunBT()
{
	running = true;
	startThread();
}

void BehaviorTree::TerminateBT()
{
	stopThread();
	if (root_ != nullptr)
	{
		root_->Terminate();
	}
	running = false;
}

void BehaviorTree::threadedFunction()
{
	while (isThreadRunning() && root_ != nullptr)
	{
		root_->startThread();
		root_->waitForThread(false);

		const std::type_info& type = typeid(*this);
	}

	const std::type_info& type = typeid(*this);
}
