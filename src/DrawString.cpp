#include "DrawString.h"

DrawString& DrawString::GetInstance()
{
	static DrawString instance;
	return instance;
}

DrawString::DrawString()
{
	font_.load("consola.ttf", 24);
	size_ = 24;
}

void DrawString::Draw(const string& text, glm::vec2 position, HorizontalAlign horizontal, VerticalAlign vertical, ofColor color)
{
	ofPushMatrix();

	switch (horizontal)
	{
	case DrawString::kHorizontalLeft:
		break;
	case DrawString::kHorizontalCenter:
		position.x -= GetInstance().font_.stringWidth(text) / 2.0f;
		break;
	case DrawString::kHorizontalRight:
		position.x -= GetInstance().font_.stringWidth(text);
		break;
	default:
		break;
	}

	switch (vertical)
	{
	case DrawString::kVerticalTop:
		break;
	case DrawString::kVerticalCenter:
		position.y -= GetInstance().font_.stringHeight(text) / 2.0f;
		break;
	case DrawString::kVerticalBottom:
		position.y -= GetInstance().font_.stringHeight(text);
		break;
	default:
		break;
	}
	ofSetColor(color);
	GetInstance().font_.drawString(text, position.x, position.y + static_cast<float>(GetInstance().size_));
	ofPopMatrix();
}

int DrawString::GetFontSize()
{
	return GetInstance().size_;
}
