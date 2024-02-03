#include "Task.h"
#include "ofLog.h"
#include "Utils.h"

void Task::threadedFunction()
{
	if (isThreadRunning()) 
	{
		//const std::type_info& type = typeid(*this);

		//ofLog(OF_LOG_NOTICE, "Task %s start", type.name());
		result_ = Run();
		//ofLog(OF_LOG_NOTICE, "Task %s end  : %d", type.name(), result_);
	}
}

Task::Task(Blackboard* blackboard) :
	result_(false), blackboard_(blackboard)
{
}

Task::Task() :
	result_(false), blackboard_(nullptr)
{
}

Task::~Task()
{
	
}

void Task::SafeCleanUp()
{
	Terminate();
	waitForThread(false);
}

void Task::Terminate()
{
	stopThread();
}