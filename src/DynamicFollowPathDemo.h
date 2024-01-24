#pragma once
#include "ofMain.h"
#include "Boid.h"
#include "DynamicFollowPath.h"
#include "DynamicLookWhereYoureGoing.h"

class DynamicFollowPathDemo
{
public:
	Boid* character_boid_;
	Path* path_;
	std::vector<glm::vec2> waypoints_;
	DynamicFollowPath* dynamic_follow_path_;
	DynamicLookWhereYoureGoing* dynamic_look_where_you_re_going;

	enum ProcessControl
	{
		kReady = 0,
		kSetBoid = 1,
		kSetPath = 2,
		kStartMove = 3,
		kMoving = 4,
		kFinished = 5,
	};

	ProcessControl process_;

	bool mouse_clicked;

	DynamicFollowPathDemo();

	void Setup();
	void Update();
	void Exit();
	void Draw();

	void DrawStrings();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
};

