#pragma once
#include "ofMain.h"
#include "Boid.h"
#include "Rigidbody.h"
#include <queue>
#include "DynamicPursue.h"
#include "DynamicSeek.h"
#include "DynamicLookWhereYoureGoing.h"

class DynamicPursueVSSeekkDemo
{
public:
	Boid* character_pursue_boid_;
	Boid* character_seek_boid_;
	Boid* target_boid_;
	DynamicPursue* dynamic_pursue_;
	DynamicSeek* dynamic_seek_;
	DynamicLookWhereYoureGoing* dynamic_pursue_look_where_youre_going_;
	DynamicLookWhereYoureGoing* dynamic_seek_look_where_youre_going_;

	DynamicPursueVSSeekkDemo();

	void Setup();
	void Update();
	void Exit();
	void Draw();
};


