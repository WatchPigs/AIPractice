#include "KinematicArriveDemo.h"
#include "Utils.h"

KinematicArriveDemo::KinematicArriveDemo() :
	boid_(nullptr), kinematic_arrive_(nullptr), on_first_(true)
{
}

void KinematicArriveDemo::Setup()
{
	boid_ = new Boid(glm::vec2(0.0f + 8.0f, ofGetHeight() - 8.0f), 0.0f, 8.0f, 16.0f, ofColor::white);
	kinematic_arrive_ = new KinematicArrive();

	waypoints_.push(new Rigidbody(glm::vec2(ofGetWidth() - boid_->radius_, ofGetHeight() - boid_->radius_), 0.0f, glm::vec2(0.0f, 0.0f), 0.0f));
	waypoints_.push(new Rigidbody(glm::vec2(ofGetWidth() - boid_->radius_, 0.0f + boid_->radius_), 0.0f, glm::vec2(0.0f, 0.0f), 0.0f));
	waypoints_.push(new Rigidbody(glm::vec2(0.0f + boid_->radius_, 0.0f + boid_->radius_), 0.0f, glm::vec2(0.0f, 0.0f), 0.0f));
	waypoints_.push(new Rigidbody(glm::vec2(0.0f + boid_->radius_, ofGetHeight() - boid_->radius_), 0.0f, glm::vec2(0.0f, 0.0f), 0.0f));
}


void KinematicArriveDemo::Update()
{
	float delta_time = ofGetLastFrameTime();

	if (!kinematic_arrive_->arrived_)
	{
		kinematic_arrive_->character_rb_->update(kinematic_arrive_->GetSteering(), delta_time);
		// Face in the direction we want to move
		kinematic_arrive_->character_rb_->orientation_ = OrientationToVec2(kinematic_arrive_->character_rb_->orientation_, kinematic_arrive_->character_rb_->velocity_);
	}
	else
	{
		if (waypoints_.size() > 0)
		{
			if (!on_first_) waypoints_.pop();
			else on_first_ = false;
		}
		if (waypoints_.size() > 0)
		{
			Rigidbody* target = waypoints_.front();
			kinematic_arrive_->NewRequest(boid_->rigidbody_, target, 512.0f, 8.0f, 0.1f);
		}
	}
	boid_->UpdateBreadcrumbs(delta_time);
}


void KinematicArriveDemo::Exit()
{
	if (boid_ != nullptr) 
	{
		delete boid_;
		boid_ = nullptr;
	}

	if (kinematic_arrive_ != nullptr)
	{
		delete kinematic_arrive_;
		kinematic_arrive_ = nullptr;
	}

	while (waypoints_.size() > 0)
	{
		Rigidbody* waypoint = waypoints_.front();
		delete waypoint;
		waypoints_.pop();
	}
}


void KinematicArriveDemo::Draw()
{
	boid_->Draw(true);
}