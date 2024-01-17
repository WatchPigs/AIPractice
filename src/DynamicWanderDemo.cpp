#include "DynamicWanderDemo.h"

DynamicWanderDemo::DynamicWanderDemo() :
	character_boid_(nullptr), dynamic_wander_(nullptr), collision_detector_(nullptr), dynamic_obstacle_avoidance_(nullptr)
{
}

void DynamicWanderDemo::Setup()
{
	character_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.75f), ofDegToRad(-90.0f), 8.0f, 16.0f, ofColor::green);
	dynamic_wander_ = new DynamicWander();
	dynamic_wander_->NewRequest(character_boid_->rigidbody_, 32.0f, 48.0f, ofDegToRad(15.0f), 64.0f, ofDegToRad(180.0f), ofDegToRad(90.0f), ofDegToRad(2.0f), ofDegToRad(30.0f), 0.1f);
	
	collision_detector_ = new CollisionDetector();
	collision_detector_->AddLineSegment(glm::vec2(0.0f, 0.0f), glm::vec2(ofGetWidth(), 0.0f));
	collision_detector_->AddLineSegment(glm::vec2(ofGetWidth(), 0.0f), glm::vec2(ofGetWidth(), ofGetHeight()));
	collision_detector_->AddLineSegment(glm::vec2(ofGetWidth(), ofGetHeight()), glm::vec2(0.0f, ofGetHeight()));
	collision_detector_->AddLineSegment(glm::vec2(0.0f, ofGetHeight()), glm::vec2(0.0f, 0.0f));
	collision_detector_->AddLineSegment(glm::vec2(0.0f, 64.0f), glm::vec2(64.0f, 0.0f));
	collision_detector_->AddLineSegment(glm::vec2(ofGetWidth() - 64.0f, 0.0f), glm::vec2(ofGetWidth(), 64.0f));
	collision_detector_->AddLineSegment(glm::vec2(ofGetWidth(), ofGetHeight() - 64.0f), glm::vec2(ofGetWidth() - 64.0f, ofGetHeight()));
	collision_detector_->AddLineSegment(glm::vec2(64.0f, ofGetHeight()), glm::vec2(0.0f, ofGetHeight() - 64.0f));
	
	dynamic_obstacle_avoidance_ = new DynamicObstacleAvoidance();
	dynamic_obstacle_avoidance_->NewRequest(character_boid_->rigidbody_, collision_detector_, 256.0f, 128.0f, 2048.0f);

}

void DynamicWanderDemo::Update()
{
	float delta_time = ofGetLastFrameTime();

	if (!dynamic_wander_->arrived_)
	{
		DynamicSteeringOutput dynamic_steering_output_wander = dynamic_wander_->GetSteering();
		DynamicSteeringOutput dynamic_steering_output_obstacle_avoidance = dynamic_obstacle_avoidance_->GetSteering();
		dynamic_wander_->character_rb_->update(dynamic_steering_output_wander + dynamic_steering_output_obstacle_avoidance, 128.0f, delta_time);
	}

	character_boid_->UpdateBreadcrumbs(delta_time);
}

void DynamicWanderDemo::Exit()
{
	if (character_boid_ != nullptr)
	{
		delete character_boid_;
		character_boid_ = nullptr;
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
	if (dynamic_obstacle_avoidance_ != nullptr)
	{
		delete dynamic_obstacle_avoidance_;
		dynamic_obstacle_avoidance_ = nullptr;
	}
}

void DynamicWanderDemo::Draw()
{
	character_boid_->Draw(true);

	// Draw target circle
	ofPushMatrix();
	ofTranslate(dynamic_wander_->circle_position_);
	ofSetColor(ofColor::yellow);
	ofNoFill();
	ofDrawCircle(0.0f, 0.0f, dynamic_wander_->wander_radius_);
	ofFill();
	ofPopMatrix();

	// Draw target
	ofPushMatrix();
	ofTranslate(dynamic_wander_->target_rb_->position_);
	ofSetColor(ofColor::yellow);
	ofDrawCircle(0.0f, 0.0f, 4.0f);
	ofPopMatrix();

	// Draw detection ray
	ofPushMatrix();

	ofTranslate(character_boid_->rigidbody_->position_);
	ofRotateRad(atan2(dynamic_obstacle_avoidance_->draw_ray_.y, dynamic_obstacle_avoidance_->draw_ray_.x));
	ofSetColor(ofColor::blue);

	ofDrawLine(glm::zero<glm::vec2>(), glm::vec2(glm::length(dynamic_obstacle_avoidance_->draw_ray_), 0.0f));

	ofPopMatrix();

	// Draw line collider
	ofPushMatrix();

	ofSetColor(ofColor::red);

	ofSetLineWidth(5.0f);
	for (auto line : collision_detector_->line_segments_) ofDrawLine(line.p1, line.p2);
	ofSetLineWidth(1.0f);

	ofPopMatrix();
}

