#include "BTTest.h"
#include "BBTest.h"
#include "UntilFail.h"
#include "Sequence.h"
#include "CheckValueTest.h"
#include "LogValueTest.h"
#include "Wait.h"
#include "Parallel.h"
#include "Inverter.h"
#include "Selector.h"
#include "LogString.h"

BTTest::BTTest()
{
	// create blackboard
	blackboard_ = new BBTest(0);
	

	// create tasks

	//UntilFail* until_fail_0 = new UntilFail();
	//all_tasks_.insert(until_fail_0);
	//root_ = until_fail_0;

	//Sequence* sequence_1_0 = new Sequence();
	//until_fail_0->SetChild(sequence_1_0);
	//all_tasks_.insert(sequence_1_0);

	//CheckValueTest* check_value_test_2_0 = new CheckValueTest(blackboard_, [](int value) { return value < 3; });
	//sequence_1_0->AddChild(check_value_test_2_0);
	//all_tasks_.insert(check_value_test_2_0);

	//LogValueTest* log_value_test_2_1 = new LogValueTest(blackboard_);
	//sequence_1_0->AddChild(log_value_test_2_1);
	//all_tasks_.insert(log_value_test_2_1);

	//Wait* wait_2_2 = new Wait(500, 20);
	//sequence_1_0->AddChild(wait_2_2);
	//all_tasks_.insert(wait_2_2);

	//------------
	//Parallel* parallel_0_0 = new Parallel();
	//root_ = parallel_0_0;
	//all_tasks_.insert(parallel_0_0);

	//Inverter* inverter_1_0 = new Inverter();
	//parallel_0_0->AddChild(inverter_1_0);
	//all_tasks_.insert(inverter_1_0);

	//Wait* wait_1_1 = new Wait(10000, 10);
	//parallel_0_0->AddChild(wait_1_1);
	//all_tasks_.insert(wait_1_1);

	//Wait* wait_2_0 = new Wait(3000, 10);
	//inverter_1_0->SetChild(wait_2_0);
	//all_tasks_.insert(wait_2_0);

	//-------------

	//Parallel* parallel_0_0 = new Parallel();
	//root_ = parallel_0_0;
	//all_tasks_.insert(parallel_0_0);

	//UntilFail* until_fail_1_0 = new UntilFail();
	//parallel_0_0->AddChild(until_fail_1_0);
	//all_tasks_.insert(until_fail_1_0);

	//UntilFail* until_fail_1_1 = new UntilFail();
	//parallel_0_0->AddChild(until_fail_1_1);
	//all_tasks_.insert(until_fail_1_1);

	//-------------
	
	//Selector* selector_0_0 = new Selector();
	//root_ = selector_0_0;
	//all_tasks_.insert(selector_0_0);

	//Sequence* sequence_1_0 = new Sequence();
	//selector_0_0->AddChild(sequence_1_0);
	//all_tasks_.insert(sequence_1_0);

	//Sequence* sequence_1_1 = new Sequence();
	//selector_0_0->AddChild(sequence_1_1);
	//all_tasks_.insert(sequence_1_1);

	//CheckValueTest* check_value_test_2_0 = new CheckValueTest(blackboard_, [](int value) { return value < 3; });
	//sequence_1_0->AddChild(check_value_test_2_0);
	//all_tasks_.insert(check_value_test_2_0);

	//LogString* log_string_2_1 = new LogString("value < 3");
	//sequence_1_0->AddChild(log_string_2_1);
	//all_tasks_.insert(log_string_2_1);

	//CheckValueTest* check_value_test_2_2 = new CheckValueTest(blackboard_, [](int value) { return value > 3; });
	//sequence_1_1->AddChild(check_value_test_2_2);
	//all_tasks_.insert(check_value_test_2_2);

	//LogString* log_string_2_3 = new LogString("value > 3");
	//sequence_1_1->AddChild(log_string_2_3);
	//all_tasks_.insert(log_string_2_3);
}
