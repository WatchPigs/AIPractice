#pragma once
#include "BTTest.h"

class TestDemo
{
public:
	BTTest* bt_test_;

	TestDemo();

	void Setup();
	void Update();
	void Exit();
	void Draw();

	void keyPressed(int key);
};

