#pragma once
#include "ofMain.h"
#include "Rigidbody.h"
#include <deque>

class Boid 
{
public:
	float radius_, length_;
	ofColor color_;
	
	Rigidbody* rigidbody_;

	std::deque<glm::vec2> breadcrumbs_;

	float breadcrumbs_generate_time_ = 0.05f;
	int breadcrumbs_max_amount_ = 32;

	Boid();
	Boid(glm::vec2 position, float orientation, float radius, float length, ofColor color, float mass = 1.0f);
	~Boid();

	void Draw(bool draw_bread_crumbs);
	void UpdateBreadcrumbs(float time);
	void DrawBreadcrumbs();

private:
	float breadcrumbs_generate_time_counter_ = 0.0f;
		
};

