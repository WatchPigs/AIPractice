#pragma once
#include "ofMain.h"

class DrawString
{
public:
	DrawString(const DrawString&) = delete;
	DrawString& operator=(const DrawString&) = delete;
	static DrawString& GetInstance();

	enum HorizontalAlign
	{
		kHorizontalLeft = 0,
		kHorizontalCenter = 1,
		kHorizontalRight = 2,
	};

	enum VerticalAlign
	{
		kVerticalTop = 0,
		kVerticalCenter = 1,
		kVerticalBottom = 2,
	};

	static void Draw(const string& text, glm::vec2 position, HorizontalAlign horizontal, VerticalAlign vertical, ofColor color);

private:
	ofTrueTypeFont font_;
	int size_;
	DrawString();
};

