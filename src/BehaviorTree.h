#pragma once
#include "Task.h"
#include "Blackboard.h"
#include <set>

class BehaviorTree : public ofThread
{
public:
	Blackboard* blackboard_;
	Task* root_;
	std::set<Task*> all_tasks_;
	
	bool running;

	BehaviorTree();
	virtual ~BehaviorTree();
	void SafeCleanUp();
	
	void RunBT();
	void TerminateBT();

protected:
	void threadedFunction() override;
};

