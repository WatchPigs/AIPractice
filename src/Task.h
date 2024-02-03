#pragma once
#include "ofThread.h"
#include "Blackboard.h"

class Task : public ofThread
{
public:
	
	bool result_;
	Blackboard* blackboard_;

	Task(Blackboard* blackboard);
	Task();
	virtual ~Task();
	virtual void SafeCleanUp();

	virtual void Terminate();

protected:
	// need implementation, should not be blocked unless use while(isThreadRunning())
	virtual bool Run() = 0;
	void threadedFunction() override;
};

