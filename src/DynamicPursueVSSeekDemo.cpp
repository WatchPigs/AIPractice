#include "DynamicPursueVSSeekDemo.h"
#include "Utils.h"

DynamicPursueVSSeekkDemo::DynamicPursueVSSeekkDemo() :
	character_pursue_boid_(nullptr), character_seek_boid_(nullptr), target_boid_(nullptr), dynamic_pursue_(nullptr), dynamic_seek_(nullptr), dynamic_pursue_look_where_youre_going_(nullptr), dynamic_seek_look_where_youre_going_(nullptr)
{
}

void DynamicPursueVSSeekkDemo::Setup()
{
	character_pursue_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.75f, ofGetHeight() * 0.75f), ofDegToRad(270.0f), 8.0f, 16.0f, ofColor::green);
	character_seek_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.75f, ofGetHeight() * 0.75f), ofDegToRad(270.0f), 8.0f, 16.0f, ofColor::yellow);
	
	target_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.75f, ofGetHeight() * 0.25f), ofDegToRad(90.0f), 8.0f, 16.0f, ofColor::white);

	// Set initial velocity for target
	target_boid_->rigidbody_->velocity_ = glm::vec2(-64.0f, 0.0f);

	dynamic_pursue_ = new DynamicPursue();
	dynamic_pursue_->NewRequest(character_pursue_boid_->rigidbody_, target_boid_->rigidbody_, 64.0f, 5.0f);

	dynamic_seek_ = new DynamicSeek();
	dynamic_seek_->NewRequest(character_seek_boid_->rigidbody_, target_boid_->rigidbody_, 64.0f);

	dynamic_pursue_look_where_youre_going_ = new DynamicLookWhereYoureGoing();
	dynamic_pursue_look_where_youre_going_->NewRequest(character_pursue_boid_->rigidbody_, ofDegToRad(180.0f), ofDegToRad(90.0f), ofDegToRad(2.0f), ofDegToRad(30.0f), 0.1f);

	dynamic_seek_look_where_youre_going_ = new DynamicLookWhereYoureGoing();
	dynamic_seek_look_where_youre_going_->NewRequest(character_seek_boid_->rigidbody_, ofDegToRad(180.0f), ofDegToRad(90.0f), ofDegToRad(2.0f), ofDegToRad(30.0f), 0.1f);
}

void DynamicPursueVSSeekkDemo::Update()
{
	float delta_time = ofGetLastFrameTime();

	if (!dynamic_pursue_->arrived_)
	{
		DynamicSteeringOutput dynamic_steering_output_pursue = dynamic_pursue_->GetSteering();
		DynamicSteeringOutput dynamic_steering_output_pursue_look = dynamic_pursue_look_where_youre_going_->GetSteering();
		dynamic_pursue_->character_rb_->update(dynamic_steering_output_pursue + dynamic_steering_output_pursue_look, 128.0f, delta_time);
	}
	if (!dynamic_seek_->arrived_)
	{
		DynamicSteeringOutput dynamic_steering_output_seek = dynamic_seek_->GetSteering();
		DynamicSteeringOutput dynamic_steering_output_seek_look = dynamic_seek_look_where_youre_going_->GetSteering();
		dynamic_seek_->character_rb_->update(dynamic_steering_output_seek + dynamic_steering_output_seek_look, 128.0f, delta_time);
	}

	target_boid_->rigidbody_->update(delta_time);
	target_boid_->rigidbody_->orientation_ = OrientationToVec2(target_boid_->rigidbody_->orientation_, target_boid_->rigidbody_->velocity_);

	target_boid_->UpdateBreadcrumbs(delta_time);
	character_pursue_boid_->UpdateBreadcrumbs(delta_time);
	character_seek_boid_->UpdateBreadcrumbs(delta_time);
}

void DynamicPursueVSSeekkDemo::Exit()
{
	if (character_pursue_boid_ != nullptr)
	{
		delete character_pursue_boid_;
		character_pursue_boid_ = nullptr;
	}
	if (character_seek_boid_ != nullptr)
	{
		delete character_seek_boid_;
		character_seek_boid_ = nullptr;
	}
	if (target_boid_ != nullptr)
	{
		delete target_boid_;
		target_boid_ = nullptr;
	}
	if (dynamic_pursue_ != nullptr)
	{
		delete dynamic_pursue_;
		dynamic_pursue_ = nullptr;
	}
	if (dynamic_seek_ != nullptr)
	{
		delete dynamic_seek_;
		dynamic_seek_ = nullptr;
	}
	if (dynamic_pursue_look_where_youre_going_ != nullptr)
	{
		delete dynamic_pursue_look_where_youre_going_;
		dynamic_pursue_look_where_youre_going_ = nullptr;
	}
	if (dynamic_seek_look_where_youre_going_ != nullptr)
	{
		delete dynamic_seek_look_where_youre_going_;
		dynamic_seek_look_where_youre_going_ = nullptr;
	}
}

void DynamicPursueVSSeekkDemo::Draw()
{
	target_boid_->Draw(true);
	character_seek_boid_->Draw(true);
	character_pursue_boid_->Draw(true);
}