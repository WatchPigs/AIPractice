#include "Boid.h"

Boid::Boid() :
	radius_(0.0f), length_(0.0f), color_(ofColor(0, 0, 0))
{
	rigidbody_ = new Rigidbody();
}

Boid::Boid(glm::vec2 position, float orientation, float radius, float length, ofColor color, float mass) :
	radius_(radius), length_(length), color_(color)
{
	rigidbody_ = new Rigidbody(position, orientation, glm::vec2(0.0f, 0.0f), 0.0f, mass);
}

Boid::~Boid() {}

void Boid::Draw(bool draw_bread_crumbs) 
{
	if (draw_bread_crumbs) DrawBreadcrumbs();

	ofPushMatrix();

	ofTranslate(rigidbody_->position_);
	ofRotateRad(rigidbody_->orientation_);
	ofSetColor(color_);
	
	ofDrawCircle(0, 0, radius_);

	ofDrawTriangle(0.0f, -radius_, 0.0f, radius_, length_, 0.0f);

	ofPopMatrix();
}

void Boid::UpdateBreadcrumbs(float time)
{
	breadcrumbs_generate_time_counter_ += time;
	if (breadcrumbs_generate_time_counter_ > breadcrumbs_generate_time_)
	{
		breadcrumbs_generate_time_counter_ -= breadcrumbs_generate_time_;
		breadcrumbs_.push_front(rigidbody_->position_);
	}
	while (breadcrumbs_.size() > breadcrumbs_max_amount_) breadcrumbs_.pop_back();
}

void Boid::DrawBreadcrumbs()
{
	for (int i = breadcrumbs_.size() - 1; i >= 0; i--)
	{
		float brightness = (float)(breadcrumbs_max_amount_ - i) / breadcrumbs_max_amount_;
		ofColor color = color_;
		color.a *= brightness;

		ofPushMatrix();
		ofTranslate(breadcrumbs_[i]);
		ofSetColor(color);
		ofDrawCircle(0, 0, radius_ * 0.25f);
		ofPopMatrix();
	}
}
