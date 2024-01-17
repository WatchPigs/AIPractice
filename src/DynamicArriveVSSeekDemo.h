#pragma once
#include "ofMain.h"
#include "Boid.h"
#include "Rigidbody.h"
#include <queue>
#include "DynamicArrive.h"
#include "DynamicSeek.h"
#include "DynamicLookWhereYoureGoing.h"

class DynamicArriveVSSeekDemo
{
public:
	Boid* character_arrive_boid_;
	Boid* character_seek_boid_;
	Boid* target_boid_;
	DynamicArrive* dynamic_arrive_;
	DynamicSeek* dynamic_seek_;
	DynamicLookWhereYoureGoing* dynamic_arrive_look_where_youre_going_;
	DynamicLookWhereYoureGoing* dynamic_seek_look_where_youre_going_;


	DynamicArriveVSSeekDemo();

	void Setup();
	void Update();
	void Exit();
	void Draw();
};

