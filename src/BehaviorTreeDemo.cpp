#include "BehaviorTreeDemo.h"
#include "BlackboardJR.h"
#include "DrawString.h"
#include <string>
#include <sstream>

BehaviorTreeDemo::BehaviorTreeDemo() :
	character_boid_(nullptr), behavior_tree_jr_(nullptr), collision_detector_(nullptr), dynamic_obstacle_avoidance_(nullptr), process_(kReady), mouse_clicked(false)
{
}

void BehaviorTreeDemo::Setup()
{
	character_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f), ofDegToRad(0.0f), 8.0f, 16.0f, ofColor::green);

	behavior_tree_jr_ = new BehaviorTreeJR(character_boid_->rigidbody_);

	collision_detector_ = new CollisionDetector();
	collision_detector_->AddLineSegment(glm::vec2(0.0f, 0.0f), glm::vec2(ofGetWidth(), 0.0f));
	collision_detector_->AddLineSegment(glm::vec2(ofGetWidth(), 0.0f), glm::vec2(ofGetWidth(), ofGetHeight()));
	collision_detector_->AddLineSegment(glm::vec2(ofGetWidth(), ofGetHeight()), glm::vec2(0.0f, ofGetHeight()));
	collision_detector_->AddLineSegment(glm::vec2(0.0f, ofGetHeight()), glm::vec2(0.0f, 0.0f));

	dynamic_obstacle_avoidance_ = new DynamicObstacleAvoidance();
	dynamic_obstacle_avoidance_->NewRequest(character_boid_->rigidbody_, collision_detector_, 256.0f, 16.0f, 2048.0f);

	dynamic_look_where_youre_going_ = new DynamicLookWhereYoureGoing();
	dynamic_look_where_youre_going_->NewRequest(character_boid_->rigidbody_, ofDegToRad(180.0f), ofDegToRad(90.0f), ofDegToRad(2.0f), ofDegToRad(30.0f), 0.1f);
}

void BehaviorTreeDemo::Update()
{
	float delta_time = ofGetLastFrameTime();

	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(behavior_tree_jr_->blackboard_);

	if (blackboard_jr != nullptr && !blackboard_jr->in_cleaning_up_ && blackboard_jr->notice_time_ > 0) blackboard_jr->notice_time_ -= delta_time * 1000;

	switch (process_)
	{
	case BehaviorTreeDemo::kReady:
		break;
	case BehaviorTreeDemo::kSetChargingStations:
		break;
	case BehaviorTreeDemo::kRunning:

		if (blackboard_jr != nullptr && !blackboard_jr->in_cleaning_up_ && behavior_tree_jr_->running)
		{
			if (blackboard_jr->get_kinematic_steering_ != nullptr)
			{
				KinematicSteeringOutput kinematic_steering_output_behavior_tree = blackboard_jr->GetKinematicSteering();
				character_boid_->rigidbody_->update(kinematic_steering_output_behavior_tree, delta_time);
			}
			else if (blackboard_jr->get_dynamic_steering_ != nullptr)
			{
				DynamicSteeringOutput dynamic_steering_output_behavior_tree = blackboard_jr->GetDynamicSteering();
				//dynamic_steering_output_behavior_tree.angular = 0.0f;
				DynamicSteeringOutput dynamic_steering_output_obstacle_avoidance = dynamic_obstacle_avoidance_->GetSteering();
				DynamicSteeringOutput dynamic_steering_output_look_where_youre_going_ = dynamic_look_where_youre_going_->GetSteering();
				character_boid_->rigidbody_->update(dynamic_steering_output_behavior_tree + dynamic_steering_output_obstacle_avoidance + dynamic_steering_output_look_where_youre_going_, 128.0f, delta_time);
			}
			else
			{
				DynamicSteeringOutput dynamic_steering_output_obstacle_avoidance = dynamic_obstacle_avoidance_->GetSteering();
				DynamicSteeringOutput dynamic_steering_output_look_where_youre_going_ = dynamic_look_where_youre_going_->GetSteering();
				character_boid_->rigidbody_->update(dynamic_steering_output_obstacle_avoidance + dynamic_steering_output_look_where_youre_going_, 128.0f, delta_time);
			}
			blackboard_jr->Update();
		}
		else
		{
			DynamicSteeringOutput dynamic_steering_output_obstacle_avoidance = dynamic_obstacle_avoidance_->GetSteering();
			DynamicSteeringOutput dynamic_steering_output_look_where_youre_going_ = dynamic_look_where_youre_going_->GetSteering();
			character_boid_->rigidbody_->update(dynamic_steering_output_obstacle_avoidance + dynamic_steering_output_look_where_youre_going_, 128.0f, delta_time);
		}
		character_boid_->UpdateBreadcrumbs(delta_time);
		break;
	case BehaviorTreeDemo::kFinished:
		break;
	default:
		break;
	}
}

void BehaviorTreeDemo::Exit()
{
	if (behavior_tree_jr_ != nullptr)
	{
		behavior_tree_jr_->SafeCleanUp();
		delete behavior_tree_jr_;
		behavior_tree_jr_ = nullptr;
	}
	if (character_boid_ != nullptr)
	{
		delete character_boid_;
		character_boid_ = nullptr;
	}
	if (collision_detector_ != nullptr)
	{
		delete collision_detector_;
		collision_detector_ = nullptr;
	}
	if (dynamic_obstacle_avoidance_ != nullptr)
	{
		delete dynamic_obstacle_avoidance_;
		dynamic_obstacle_avoidance_ = nullptr;
	}
}

void BehaviorTreeDemo::Draw()
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(behavior_tree_jr_->blackboard_);
	if (blackboard_jr != nullptr && !blackboard_jr->in_cleaning_up_) blackboard_jr->Draw();

	// Draw line collider
	ofPushMatrix();

	ofSetColor(ofColor::red);

	ofSetLineWidth(5.0f);
	for (CollisionDetector::LineSegment line : collision_detector_->line_segments_) ofDrawLine(line.p1, line.p2);
	ofSetLineWidth(1.0f);

	ofPopMatrix();

	character_boid_->Draw(true);

	DrawStrings();
}

void BehaviorTreeDemo::DrawStrings()
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(behavior_tree_jr_->blackboard_);
	switch (process_)
	{
	case BehaviorTreeDemo::kReady:
		break;
	case BehaviorTreeDemo::kSetChargingStations:
		if (blackboard_jr != nullptr && !blackboard_jr->in_cleaning_up_)
		{
			std::stringstream set_charging_stations_string_stream;
			set_charging_stations_string_stream << "Left click anywhere to create charging stations\n" << " (min number: " << blackboard_jr->min_charging_stations_size_ << ", max number: " << blackboard_jr->max_charging_stations_size_ << ")\nPress ENTER to finish this step";
			DrawString::Draw(set_charging_stations_string_stream.str(), glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
		}
		break;
	case BehaviorTreeDemo::kRunning:
		if (blackboard_jr != nullptr && !blackboard_jr->in_cleaning_up_)
		{
			if (blackboard_jr->notice_time_ > 0)
			{
				std::shared_lock<std::shared_mutex> lock_notice_string(blackboard_jr->mtx_notice_string_);
				DrawString::Draw(blackboard_jr->notice_string_, glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
			}

			std::stringstream power_string_stream;
			power_string_stream << "Power: " << blackboard_jr->power_ << " / " << blackboard_jr->max_power_;
			DrawString::Draw(power_string_stream.str(), glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.15f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
			
			std::shared_lock<std::shared_mutex> lock_status_string(blackboard_jr->mtx_status_string_);
			DrawString::Draw(blackboard_jr->status_string_, glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.15f + DrawString::GetFontSize() * 1.5f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
		}
		break;
	case BehaviorTreeDemo::kFinished:
		break;
	default:
		break;
	}
}

void BehaviorTreeDemo::keyPressed(int key)
{
	BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(behavior_tree_jr_->blackboard_);
	switch (process_)
	{
	case BehaviorTreeDemo::kReady:
		break;
	case BehaviorTreeDemo::kSetChargingStations:
		if (key == OF_KEY_RETURN)
		{
			if (blackboard_jr != nullptr && !blackboard_jr->in_cleaning_up_)
			{
				int charging_stations_size = blackboard_jr->GetChargingStationsSize();
				if (charging_stations_size >= blackboard_jr->min_charging_stations_size_ && charging_stations_size <= blackboard_jr->max_charging_stations_size_)
				{
					process_ = kRunning;
					behavior_tree_jr_->RunBT();
					std::unique_lock<std::shared_mutex> lock_notice_string(blackboard_jr->mtx_notice_string_);
					std::stringstream set_charging_stations_string_stream;
					set_charging_stations_string_stream << "Left click anywhere to create trashes\n" << " (max number: " << blackboard_jr->max_trashes_size_ << ")";
					blackboard_jr->notice_string_ = set_charging_stations_string_stream.str();
					blackboard_jr->notice_time_ += 5000;
				}
			}
		}
		break;
	case BehaviorTreeDemo::kRunning:
		break;
	case BehaviorTreeDemo::kFinished:
		break;
	default:
		break;
	}
}

void BehaviorTreeDemo::mousePressed(int x, int y, int button)
{
	switch (process_)
	{
	case BehaviorTreeDemo::kReady:
		break;
	case BehaviorTreeDemo::kSetChargingStations:
		if (button == 0 && !mouse_clicked)
		{
			mouse_clicked = true;
			BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(behavior_tree_jr_->blackboard_);
			if (blackboard_jr != nullptr && !blackboard_jr->in_cleaning_up_)
			{
				int charging_stations_size = blackboard_jr->GetChargingStationsSize();
				if (charging_stations_size < blackboard_jr->max_charging_stations_size_)
				{
					glm::vec2 position = glm::vec2(static_cast<float>(x), static_cast<float>(y));
					blackboard_jr->AddChargingStation(position, 32.0f, ofColor::yellow);
				}
			}
		}
		break;
	case BehaviorTreeDemo::kRunning:
		if (button == 0 && !mouse_clicked)
		{
			mouse_clicked = true;
			BlackboardJR* blackboard_jr = dynamic_cast<BlackboardJR*>(behavior_tree_jr_->blackboard_);
			if (blackboard_jr != nullptr && !blackboard_jr->in_cleaning_up_)
			{
				int trashes_size = blackboard_jr->GetTrashesSize();
				if (trashes_size < blackboard_jr->max_trashes_size_)
				{
					glm::vec2 position = glm::vec2(static_cast<float>(x), static_cast<float>(y));
					blackboard_jr->AddTrash(position, 16.0f, ofColor::red);
				}
			}
		}
		break;
	case BehaviorTreeDemo::kFinished:
		break;
	default:
		break;
	}
}

void BehaviorTreeDemo::mouseReleased(int x, int y, int button)
{
	if (button == 0 && mouse_clicked)
	{
		mouse_clicked = false;
	}
}
