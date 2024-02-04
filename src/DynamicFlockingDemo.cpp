#include "DynamicFlockingDemo.h"

DynamicFlockingDemo::DynamicFlockingDemo() :
	character_leader_boid_(nullptr), dynamic_wander_(nullptr), collision_detector_(nullptr), dynamic_obstacle_avoidance_leader_(nullptr)
{
}

void DynamicFlockingDemo::Setup()
{
	character_leader_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f), ofDegToRad(-90.0f), 8.0f, 16.0f, ofColor::blue, 20.0f);
	dynamic_wander_ = new DynamicWander();
	dynamic_wander_->NewRequest(character_leader_boid_->rigidbody_, 80.0f, 48.0f, ofDegToRad(15.0f), 16.0f, ofDegToRad(180.0f), ofDegToRad(90.0f), ofDegToRad(2.0f), ofDegToRad(30.0f), 0.1f);
	collision_detector_ = new CollisionDetector();
	collision_detector_->AddLineSegment(glm::vec2(0.0f, 0.0f), glm::vec2(ofGetWidth(), 0.0f));
	collision_detector_->AddLineSegment(glm::vec2(ofGetWidth(), 0.0f), glm::vec2(ofGetWidth(), ofGetHeight()));
	collision_detector_->AddLineSegment(glm::vec2(ofGetWidth(), ofGetHeight()), glm::vec2(0.0f, ofGetHeight()));
	collision_detector_->AddLineSegment(glm::vec2(0.0f, ofGetHeight()), glm::vec2(0.0f, 0.0f));
	collision_detector_->AddLineSegment(glm::vec2(0.0f, 64.0f), glm::vec2(64.0f, 0.0f));
	collision_detector_->AddLineSegment(glm::vec2(ofGetWidth() - 64.0f, 0.0f), glm::vec2(ofGetWidth(), 64.0f));
	collision_detector_->AddLineSegment(glm::vec2(ofGetWidth(), ofGetHeight() - 64.0f), glm::vec2(ofGetWidth() - 64.0f, ofGetHeight()));
	collision_detector_->AddLineSegment(glm::vec2(64.0f, ofGetHeight()), glm::vec2(0.0f, ofGetHeight() - 64.0f));
	dynamic_obstacle_avoidance_leader_ = new DynamicObstacleAvoidance();
	dynamic_obstacle_avoidance_leader_->NewRequest(character_leader_boid_->rigidbody_, collision_detector_, 512.0f, 128.0f, 2048.0f);

	// Create 8 followers
	std::vector<Rigidbody*> character_boids_rbs;
	character_boids_rbs.push_back(character_leader_boid_->rigidbody_);
	float init_interval = 64.0f;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0)
			{
				character_follower_boids_.push_back(new Boid(glm::vec2(character_leader_boid_->rigidbody_->position_.x + j * init_interval, character_leader_boid_->rigidbody_->position_.y + i * init_interval), ofDegToRad(-90.0f), 8.0f, 16.0f, ofColor::green));
				character_boids_rbs.push_back(character_follower_boids_.back()->rigidbody_);
			}
		}
	}

	for (auto character_follower_boid : character_follower_boids_)
	{
		dynamic_flockings_.push_back(new DynamicFlocking());

		std::vector<Rigidbody*> targets = character_boids_rbs;
		std::vector<Rigidbody*>::iterator self;
		for (auto it = targets.begin(); it != targets.end(); it++)
		{
			if (*it == character_follower_boid->rigidbody_) self = it;
		}
		targets.erase(self);

		dynamic_flockings_.back()->NewRequest(character_follower_boid->rigidbody_, targets,
			64.0f, 2048.f, 2048.0f,
			ofDegToRad(90.0f), ofDegToRad(45.0f), ofDegToRad(2.0f), ofDegToRad(30.0f), 0.1f,
			32.0f, 0.1f,
			64.0f, 128.0f, 4.0f, 128.0f, 0.1f,
			10.0f, 0.2f, 0.2f, 2.0f,
			256.0f, 90.0f
			);

		dynamic_obstacle_avoidance_followers_.push_back(new DynamicObstacleAvoidance());
		dynamic_obstacle_avoidance_followers_.back()->NewRequest(character_follower_boid->rigidbody_, collision_detector_, 512.0f, 128.0f, 4096.0f);
	}
}

void DynamicFlockingDemo::Update()
{
	float delta_time = ofGetLastFrameTime();

	if (!dynamic_wander_->arrived_)
	{
		DynamicSteeringOutput dynamic_steering_output_wander = dynamic_wander_->GetSteering();
		DynamicSteeringOutput dynamic_steering_output_obstacle_avoidance = dynamic_obstacle_avoidance_leader_->GetSteering();
		dynamic_wander_->character_rb_->update(dynamic_steering_output_wander + dynamic_steering_output_obstacle_avoidance, 128.0f, delta_time);
	}

	for (int i = 0; i < character_follower_boids_.size(); i++)
	{
		if (!dynamic_flockings_[i]->arrived_)
		{
			DynamicSteeringOutput dynamic_steering_output_flocking = dynamic_flockings_[i]->GetSteering();
			DynamicSteeringOutput dynamic_steering_output_obstacle_avoidance = dynamic_obstacle_avoidance_followers_[i]->GetSteering();
			dynamic_flockings_[i]->character_rb_->update(dynamic_steering_output_flocking + dynamic_steering_output_obstacle_avoidance, 128.0f, delta_time);
		}
	}

	character_leader_boid_->UpdateBreadcrumbs(delta_time);
	for (Boid* character_follower_boid : character_follower_boids_) character_follower_boid->UpdateBreadcrumbs(delta_time);
}

void DynamicFlockingDemo::Exit()
{
	if (character_leader_boid_ != nullptr)
	{
		delete character_leader_boid_;
		character_leader_boid_ = nullptr;
	}
	while (character_follower_boids_.size() > 0)
	{
		delete character_follower_boids_.back();
		character_follower_boids_.pop_back();
	}
	if (dynamic_wander_ != nullptr)
	{
		delete dynamic_wander_;
		dynamic_wander_ = nullptr;
	}
	if (collision_detector_ != nullptr)
	{
		delete collision_detector_;
		collision_detector_ = nullptr;
	}
	if (dynamic_obstacle_avoidance_leader_ != nullptr)
	{
		delete dynamic_obstacle_avoidance_leader_;
		dynamic_obstacle_avoidance_leader_ = nullptr;
	}
	while (dynamic_flockings_.size() > 0)
	{
		delete dynamic_flockings_.back();
		dynamic_flockings_.pop_back();
	}
	while (dynamic_obstacle_avoidance_followers_.size() > 0)
	{
		delete dynamic_obstacle_avoidance_followers_.back();
		dynamic_obstacle_avoidance_followers_.pop_back();
	}
}

void DynamicFlockingDemo::Draw()
{
	character_leader_boid_->Draw(true);
	for (Boid* character_follower_boid : character_follower_boids_)
	{
		character_follower_boid->Draw(true);
	}

	// Draw line collider
	ofPushMatrix();

	ofSetColor(ofColor::red);

	ofSetLineWidth(5.0f);
	for (CollisionDetector::LineSegment line : collision_detector_->line_segments_) ofDrawLine(line.p1, line.p2);
	ofSetLineWidth(1.0f);

	ofPopMatrix();
}
