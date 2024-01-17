#include "DynamicFaceDemo.h"
#include "Utils.h"

DynamicFaceDemo::DynamicFaceDemo() :
	character_face_boid_(nullptr), target_boid_(nullptr), kinematic_arrive_(nullptr), dynamic_face_(nullptr), iter(0)
{
}

void DynamicFaceDemo::Setup()
{
	character_face_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.95f), 0.0f, 8.0f, 16.0f, ofColor::green);
	target_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.25f, ofGetHeight() * 0.7f), 0.0f, 8.0f, 16.0f, ofColor::white);

	kinematic_arrive_ = new KinematicArrive();
	target_waypoints_.push_back(new Rigidbody(glm::vec2(ofGetWidth() * 0.75f, ofGetHeight() * 0.7f), 0.0f, glm::vec2(0.0f, 0.0f), 0.0f));
	target_waypoints_.push_back(new Rigidbody(glm::vec2(ofGetWidth() * 0.25f, ofGetHeight() * 0.7f), 0.0f, glm::vec2(0.0f, 0.0f), 0.0f));

	dynamic_face_ = new DynamicFace();
	dynamic_face_->NewRequest(character_face_boid_->rigidbody_, target_boid_->rigidbody_, ofDegToRad(180.0f), ofDegToRad(90.0f), ofDegToRad(2.0f), ofDegToRad(30.0f), 0.1f);
}

void DynamicFaceDemo::Update()
{
	float delta_time = ofGetLastFrameTime();

	if (!dynamic_face_->arrived_)
	{
		DynamicSteeringOutput dynamic_steering_output = dynamic_face_->GetSteering();
		dynamic_face_->character_rb_->update(dynamic_steering_output, 1024.0f, delta_time);
	}

	if (!kinematic_arrive_->arrived_)
	{
		kinematic_arrive_->character_rb_->update(kinematic_arrive_->GetSteering(), delta_time);
		// Face in the direction we want to move
		kinematic_arrive_->character_rb_->orientation_ = OrientationToVec2(kinematic_arrive_->character_rb_->orientation_, kinematic_arrive_->character_rb_->velocity_);
	}
	else
	{
		iter = (iter + 1) % target_waypoints_.size();
		kinematic_arrive_->NewRequest(target_boid_->rigidbody_, target_waypoints_[iter], 128.0f, 8.0f, 0.1f);
	}
	target_boid_->UpdateBreadcrumbs(delta_time);
}

void DynamicFaceDemo::Exit()
{
	if (character_face_boid_ != nullptr)
	{
		delete character_face_boid_;
		character_face_boid_ = nullptr;
	}
	if (target_boid_ != nullptr)
	{
		delete target_boid_;
		target_boid_ = nullptr;
	}
	if (kinematic_arrive_ != nullptr)
	{
		delete kinematic_arrive_;
		kinematic_arrive_ = nullptr;
	}
	if (dynamic_face_ != nullptr)
	{
		delete dynamic_face_;
		dynamic_face_ = nullptr;
	}
	while (target_waypoints_.size() > 0)
	{
		delete target_waypoints_.back();
		target_waypoints_.pop_back();
	}
}

void DynamicFaceDemo::Draw()
{
	target_boid_->Draw(true);
	character_face_boid_->Draw(false);

	// Draw orientation line
	ofPushMatrix();

	ofTranslate(character_face_boid_->rigidbody_->position_);
	ofRotateRad(character_face_boid_->rigidbody_->orientation_);
	ofSetColor(character_face_boid_->color_);

	ofDrawLine(glm::zero<glm::vec2>(), glm::vec2(ofGetHeight() * 0.375f, 0.0f));

	ofPopMatrix();
}

