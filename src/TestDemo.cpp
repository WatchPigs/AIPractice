#include "TestDemo.h"
#include "BBTest.h"
#include "ofLog.h"
#include <shared_mutex>

TestDemo::TestDemo() :
	bt_test_(nullptr)
{
}

void TestDemo::Setup()
{
	bt_test_ = new BTTest();
}

void TestDemo::Update()
{

}

void TestDemo::Exit()
{
	if (bt_test_ != nullptr)
	{
		ofLog(OF_LOG_NOTICE, "clean up BT test");
		bt_test_->SafeCleanUp();
		delete bt_test_;
		bt_test_ = nullptr;
	}
}

void TestDemo::Draw()
{

}

void TestDemo::keyPressed(int key)
{
	if (bt_test_ != nullptr)
	{
		if (key == 'R' || key == 'r')
		{
			if (bt_test_->isThreadDone()) bt_test_->RunBT();
		}
		if (key == 'T' || key == 't')
		{
			if (bt_test_->isThreadRunning()) bt_test_->TerminateBT();
		}
		if (key == '1')
		{
			BBTest* bb_test = dynamic_cast<BBTest*>(bt_test_->blackboard_);
			if (bb_test != nullptr)
			{
				std::unique_lock<std::shared_mutex> lock(bb_test->mtx_, std::defer_lock);
				if (lock.try_lock())
				{
					bb_test->value_ = 1;
					lock.unlock();
				}
			}
		}
		if (key == '4')
		{
			BBTest* bb_test = dynamic_cast<BBTest*>(bt_test_->blackboard_);
			if (bb_test != nullptr)
			{
				std::unique_lock<std::shared_mutex> lock(bb_test->mtx_, std::defer_lock);
				if (lock.try_lock())
				{
					bb_test->value_ = 4;
					lock.unlock();
				}
			}
		}
	}
}
