#include "LogValueTest.h"
#include "ofLog.h"

LogValueTest::LogValueTest(Blackboard* bb_test) :
	Task(bb_test)
{
}

bool LogValueTest::Run()
{
	BBTest* bb_test = dynamic_cast<BBTest*>(blackboard_);
	bool result = false;
	if (bb_test == nullptr || bb_test->in_cleaning_up_) return false;
	else
	{
		std::shared_lock<std::shared_mutex> lock_in_use(bb_test->mtx_bb_in_use_);
		std::shared_lock<std::shared_mutex> lock(bb_test->mtx_, std::defer_lock);
		while (isThreadRunning())
		{
			if (lock.try_lock())
			{
				ofLog(OF_LOG_NOTICE, "Value is %d", bb_test->value_);
				result = true;
				lock.unlock();
				break;
			}
		}
	}
	return result;
}
