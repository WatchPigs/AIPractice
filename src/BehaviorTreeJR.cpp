#include "BehaviorTreeJR.h"
#include "BlackboardJR.h"
#include "DetectFullPower.h"
#include "DetectSufficientPower.h"
#include "DetectTrash.h"
#include "MoveToTarget.h"
#include "Recharge.h"
#include "SetNearestChargingStationAsTarget.h"
#include "SetNearestTrashAsTarget.h"
#include "TidyTrash.h"
#include "UntilFail.h"
#include "Sequence.h"
#include "Parallel.h"
#include "Inverter.h"
#include "Selector.h"
#include "LogString.h"
#include "Wait.h"
#include "Wander.h"


BehaviorTreeJR::BehaviorTreeJR(Rigidbody* character_rb)
{
	blackboard_ = new BlackboardJR(character_rb, 5, 5, 5, 1, 3);

	//Parallel* parallel_0_0 = new Parallel();
	//root_ = parallel_0_0;
	//all_tasks_.insert(parallel_0_0);

	//Inverter* inverter_1_0 = new Inverter();
	//parallel_0_0->AddChild(inverter_1_0);
	//all_tasks_.insert(inverter_1_0);

	//UntilFail* until_fail_1_1 = new UntilFail();
	//parallel_0_0->AddChild(until_fail_1_1);
	//all_tasks_.insert(until_fail_1_1);

	//UntilFail* until_fail_2_0 = new UntilFail();
	//inverter_1_0->SetChild(until_fail_2_0);
	//all_tasks_.insert(until_fail_2_0);

	//Sequence* sequence_2_1 = new Sequence();
	//until_fail_1_1->SetChild(sequence_2_1);
	//all_tasks_.insert(sequence_2_1);

	//Sequence* sequence_3_0 = new Sequence();
	//until_fail_2_0->SetChild(sequence_3_0);
	//all_tasks_.insert(sequence_3_0);

	//DetectSufficientPower* detect_sufficient_power_3_1 = new DetectSufficientPower(blackboard_);
	//sequence_2_1->AddChild(detect_sufficient_power_3_1);
	//all_tasks_.insert(detect_sufficient_power_3_1);

	//SetNearestTrashAsTarget* set_nearest_trash_as_target_3_2 = new SetNearestTrashAsTarget(blackboard_);
	//sequence_2_1->AddChild(set_nearest_trash_as_target_3_2);
	//all_tasks_.insert(set_nearest_trash_as_target_3_2);

	//MoveToTarget* move_to_target_3_3 = new MoveToTarget(blackboard_);
	//sequence_2_1->AddChild(move_to_target_3_3);
	//all_tasks_.insert(move_to_target_3_3);

	//TidyTrash* tidy_trash_3_4 = new TidyTrash(blackboard_, 1000, 20);
	//sequence_2_1->AddChild(tidy_trash_3_4);
	//all_tasks_.insert(tidy_trash_3_4);

	//DetectTrash* detect_trash_4_0 = new DetectTrash(blackboard_);
	//sequence_3_0->AddChild(detect_trash_4_0);
	//all_tasks_.insert(detect_trash_4_0);

	//Wait* wait_4_1 = new Wait(200, 20);
	//sequence_3_0->AddChild(wait_4_1);
	//all_tasks_.insert(wait_4_1);


	Selector* selector_0_0 = new Selector();
	root_ = selector_0_0;
	all_tasks_.insert(selector_0_0);

	Parallel* parallel_1_0 = new Parallel();
	selector_0_0->AddChild(parallel_1_0);
	all_tasks_.insert(parallel_1_0);

	Parallel* parallel_1_1 = new Parallel();
	selector_0_0->AddChild(parallel_1_1);
	all_tasks_.insert(parallel_1_1);

	Inverter* inverter_2_0 = new Inverter();
	parallel_1_0->AddChild(inverter_2_0);
	all_tasks_.insert(inverter_2_0);

	Inverter* inverter_2_1 = new Inverter();
	parallel_1_0->AddChild(inverter_2_1);
	all_tasks_.insert(inverter_2_1);

	Inverter* inverter_2_2 = new Inverter();
	parallel_1_1->AddChild(inverter_2_2);
	all_tasks_.insert(inverter_2_2);

	UntilFail* until_fail_2_3 = new UntilFail();
	parallel_1_1->AddChild(until_fail_2_3);
	all_tasks_.insert(until_fail_2_3);

	UntilFail* until_fail_3_0 = new UntilFail();
	inverter_2_0->SetChild(until_fail_3_0);
	all_tasks_.insert(until_fail_3_0);

	UntilFail* until_fail_3_1 = new UntilFail();
	inverter_2_1->SetChild(until_fail_3_1);
	all_tasks_.insert(until_fail_3_1);

	UntilFail* until_fail_3_2 = new UntilFail();
	inverter_2_2->SetChild(until_fail_3_2);
	all_tasks_.insert(until_fail_3_2);

	Selector* selector_3_3 = new Selector();
	until_fail_2_3->SetChild(selector_3_3);
	all_tasks_.insert(selector_3_3);

	Sequence* sequence_4_0 = new Sequence();
	until_fail_3_0->SetChild(sequence_4_0);
	all_tasks_.insert(sequence_4_0);

	Selector* selector_4_1 = new Selector();
	until_fail_3_1->SetChild(selector_4_1);
	all_tasks_.insert(selector_4_1);

	Sequence* sequence_4_2 = new Sequence();
	until_fail_3_2->SetChild(sequence_4_2);
	all_tasks_.insert(sequence_4_2);

	Sequence* sequence_4_3 = new Sequence();
	selector_3_3->AddChild(sequence_4_3);
	all_tasks_.insert(sequence_4_3);

	Sequence* sequence_4_4 = new Sequence();
	selector_3_3->AddChild(sequence_4_4);
	all_tasks_.insert(sequence_4_4);

	DetectTrash* detect_trash_5_0 = new DetectTrash(blackboard_);
	sequence_4_0->AddChild(detect_trash_5_0);
	all_tasks_.insert(detect_trash_5_0);

	Wait* wait_5_1 = new Wait(200, 50);
	sequence_4_0->AddChild(wait_5_1);
	all_tasks_.insert(wait_5_1);

	Sequence* sequence_5_2 = new Sequence();
	selector_4_1->AddChild(sequence_5_2);
	all_tasks_.insert(sequence_5_2);

	Sequence* sequence_5_3 = new Sequence();
	selector_4_1->AddChild(sequence_5_3);
	all_tasks_.insert(sequence_5_3);

	Inverter* inverter_5_4 = new Inverter();
	sequence_4_2->AddChild(inverter_5_4);
	all_tasks_.insert(inverter_5_4);

	Wait* wait_5_5 = new Wait(200, 50);
	sequence_4_2->AddChild(wait_5_5);
	all_tasks_.insert(wait_5_5);

	DetectFullPower* detect_full_power_5_6 = new DetectFullPower(blackboard_);
	sequence_4_3->AddChild(detect_full_power_5_6);
	all_tasks_.insert(detect_full_power_5_6);

	Wander* wander_5_7 = new Wander(blackboard_);
	sequence_4_3->AddChild(wander_5_7);
	all_tasks_.insert(wander_5_7);

	SetNearestChargingStationAsTarget* set_nearest_charging_station_as_target_5_8 = new SetNearestChargingStationAsTarget(blackboard_);
	sequence_4_4->AddChild(set_nearest_charging_station_as_target_5_8);
	all_tasks_.insert(set_nearest_charging_station_as_target_5_8);

	MoveToTarget* move_to_target_5_9 = new MoveToTarget(blackboard_);
	sequence_4_4->AddChild(move_to_target_5_9);
	all_tasks_.insert(move_to_target_5_9);

	Recharge* recharge_5_10 = new Recharge(blackboard_, 1000, 50);
	sequence_4_4->AddChild(recharge_5_10);
	all_tasks_.insert(recharge_5_10);

	DetectSufficientPower* detect_sufficient_power_6_0 = new DetectSufficientPower(blackboard_);
	sequence_5_2->AddChild(detect_sufficient_power_6_0);
	all_tasks_.insert(detect_sufficient_power_6_0);

	SetNearestTrashAsTarget* set_nearest_trash_as_target_6_1 = new SetNearestTrashAsTarget(blackboard_);
	sequence_5_2->AddChild(set_nearest_trash_as_target_6_1);
	all_tasks_.insert(set_nearest_trash_as_target_6_1);

	MoveToTarget* move_to_target_6_2 = new MoveToTarget(blackboard_);
	sequence_5_2->AddChild(move_to_target_6_2);
	all_tasks_.insert(move_to_target_6_2);

	TidyTrash* tidy_trash_6_3 = new TidyTrash(blackboard_, 1000, 50);
	sequence_5_2->AddChild(tidy_trash_6_3);
	all_tasks_.insert(tidy_trash_6_3);

	Inverter* inverter_6_4 = new Inverter();
	sequence_5_3->AddChild(inverter_6_4);
	all_tasks_.insert(inverter_6_4);

	SetNearestChargingStationAsTarget* set_nearest_charging_station_as_target_6_5 = new SetNearestChargingStationAsTarget(blackboard_);
	sequence_5_3->AddChild(set_nearest_charging_station_as_target_6_5);
	all_tasks_.insert(set_nearest_charging_station_as_target_6_5);

	MoveToTarget* move_to_target_6_6 = new MoveToTarget(blackboard_);
	sequence_5_3->AddChild(move_to_target_6_6);
	all_tasks_.insert(move_to_target_6_6);

	Recharge* recharge_6_7 = new Recharge(blackboard_, 1000, 50);
	sequence_5_3->AddChild(recharge_6_7);
	all_tasks_.insert(recharge_6_7);

	DetectTrash* detect_trash_6_8 = new DetectTrash(blackboard_);
	inverter_5_4->SetChild(detect_trash_6_8);
	all_tasks_.insert(detect_trash_6_8);
	
	DetectSufficientPower* detect_sufficient_power_7_0 = new DetectSufficientPower(blackboard_);
	inverter_6_4->SetChild(detect_sufficient_power_7_0);
	all_tasks_.insert(detect_sufficient_power_7_0);

}
