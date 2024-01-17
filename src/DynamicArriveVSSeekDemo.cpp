#include "DynamicArriveVSSeekDemo.h"
#include "Utils.h"

DynamicArriveVSSeekDemo::DynamicArriveVSSeekDemo() :
	character_arrive_boid_(nullptr), character_seek_boid_(nullptr), target_boid_(nullptr), dynamic_arrive_(nullptr), dynamic_seek_(nullptr), dynamic_arrive_look_where_youre_going_(nullptr), dynamic_seek_look_where_youre_going_(nullptr)
{
}

void DynamicArriveVSSeekDemo::Setup()
{
	character_arrive_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.25f, ofGetHeight() * 0.5f), ofDegToRad(-90.0f), 8.0f, 16.0f, ofColor::green);
	character_seek_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.25f, ofGetHeight() * 0.5f), ofDegToRad(-90.0f), 8.0f, 16.0f, ofColor::yellow);

	// Set initial upward velocity
	character_arrive_boid_->rigidbody_->velocity_ = glm::vec2(0.0f, -64.0f);
	character_seek_boid_->rigidbody_->velocity_ = glm::vec2(0.0f, -64.0f);

	target_boid_ = new Boid(glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f), ofDegToRad(90.0f), 8.0f, 16.0f, ofColor::white);
	
	dynamic_arrive_ = new DynamicArrive();
	dynamic_arrive_->NewRequest(character_arrive_boid_->rigidbody_, target_boid_->rigidbody_, 32.0f, 128.0f, 8.0f, 128.0f, 0.1f);

	dynamic_seek_ = new DynamicSeek();
	dynamic_seek_->NewRequest(character_seek_boid_->rigidbody_, target_boid_->rigidbody_, 32.0f);

	dynamic_arrive_look_where_youre_going_ = new DynamicLookWhereYoureGoing();
	dynamic_arrive_look_where_youre_going_->NewRequest(character_arrive_boid_->rigidbody_, ofDegToRad(180.0f), ofDegToRad(90.0f), ofDegToRad(2.0f), ofDegToRad(30.0f), 0.1f);

	dynamic_seek_look_where_youre_going_ = new DynamicLookWhereYoureGoing();
	dynamic_seek_look_where_youre_going_->NewRequest(character_seek_boid_->rigidbody_, ofDegToRad(180.0f), ofDegToRad(90.0f), ofDegToRad(2.0f), ofDegToRad(30.0f), 0.1f);
}

void DynamicArriveVSSeekDemo::Update()
{
	float delta_time = ofGetLastFrameTime();

	if (!dynamic_arrive_->arrived_)
	{
		DynamicSteeringOutput dynamic_steering_output_arrive = dynamic_arrive_->GetSteering();
		DynamicSteeringOutput dynamic_steering_output_arrive_look = dynamic_arrive_look_where_youre_going_->GetSteering();
		dynamic_arrive_->character_rb_->update(dynamic_steering_output_arrive + dynamic_steering_output_arrive_look, 128.0f, delta_time);
	}
	if (!dynamic_seek_->arrived_)
	{
		DynamicSteeringOutput dynamic_steering_output_seek = dynamic_seek_->GetSteering();
		DynamicSteeringOutput dynamic_steering_output_seek_look = dynamic_seek_look_where_youre_going_->GetSteering();
		dynamic_seek_->character_rb_->update(dynamic_steering_output_seek + dynamic_steering_output_seek_look, 128.0f, delta_time);
	}
	character_arrive_boid_->UpdateBreadcrumbs(delta_time);
	character_seek_boid_->UpdateBreadcrumbs(delta_time);
}

void DynamicArriveVSSeekDemo::Exit()
{
	if (character_arrive_boid_ != nullptr)
	{
		delete character_arrive_boid_;
		character_arrive_boid_ = nullptr;
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
	if (dynamic_arrive_ != nullptr)
	{
		delete dynamic_arrive_;
		dynamic_arrive_ = nullptr;
	}
	if (dynamic_seek_ != nullptr)
	{
		delete dynamic_seek_;
		dynamic_seek_ = nullptr;
	}
	if (dynamic_arrive_look_where_youre_going_ != nullptr)
	{
		delete dynamic_arrive_look_where_youre_going_;
		dynamic_arrive_look_where_youre_going_ = nullptr;
	}
	if (dynamic_seek_look_where_youre_going_ != nullptr)
	{
		delete dynamic_seek_look_where_youre_going_;
		dynamic_seek_look_where_youre_going_ = nullptr;
	}
}

void DynamicArriveVSSeekDemo::Draw()
{
	target_boid_->Draw(false);
	character_seek_boid_->Draw(true);
	character_arrive_boid_->Draw(true);

	// Draw slow radius
	if (dynamic_arrive_->slow_radius_ > 0.01f)
	{
		ofPushMatrix();
		ofTranslate(target_boid_->rigidbody_->position_);
		ofSetColor(ofColor::yellow);
		ofNoFill();
		ofDrawCircle(0, 0, dynamic_arrive_->slow_radius_);
		ofFill();
		ofPopMatrix();
	}
}
