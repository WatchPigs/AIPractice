#include "CheckValueTest.h"

CheckValueTest::CheckValueTest(Blackboard* bb_test, std::function<bool(int)> checker) :
	Task(bb_test), checker_(checker)
{
}


bool CheckValueTest::Run()
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
				result = checker_(bb_test->value_);
				lock.unlock();
				break;
			}
		}
	}
	return result;
}
