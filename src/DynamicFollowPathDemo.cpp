#include "DynamicFollowPathDemo.h"
#include "DrawString.h"

DynamicFollowPathDemo::DynamicFollowPathDemo() :
	character_boid_(nullptr), path_(nullptr), dynamic_follow_path_(nullptr), process_(kReady), mouse_clicked(false)
{
}

void DynamicFollowPathDemo::Setup()
{
}

void DynamicFollowPathDemo::Update()
{
	float delta_time = ofGetLastFrameTime();

	switch (process_)
	{
	case DynamicFollowPathDemo::kReady:
		break;
	case DynamicFollowPathDemo::kSetBoid:
		break;
	case DynamicFollowPathDemo::kSetPath:
		break;
	case DynamicFollowPathDemo::kStartMove:
		if (path_ != nullptr)
		{
			process_ = kMoving;
			dynamic_follow_path_ = new DynamicFollowPath();
			dynamic_follow_path_->NewRequest(character_boid_->rigidbody_, path_, 64.0f, 3, 64.0f, 512.0f);
			dynamic_look_where_you_re_going = new DynamicLookWhereYoureGoing();
			dynamic_look_where_you_re_going->NewRequest(character_boid_->rigidbody_, ofDegToRad(720.0f), ofDegToRad(360.0f), ofDegToRad(2.0f), ofDegToRad(15.0f), 0.1f);
		}
		break;
	case DynamicFollowPathDemo::kMoving:
		if (!dynamic_follow_path_->arrived_)
		{
			DynamicSteeringOutput dynamic_steering_output_follow_path = dynamic_follow_path_->GetSteering();
			DynamicSteeringOutput dynamic_steering_output_look_where_you_re_going = dynamic_look_where_you_re_going->GetSteering();
			dynamic_follow_path_->character_rb_->update(dynamic_steering_output_follow_path + dynamic_steering_output_look_where_you_re_going, 128.0f, delta_time);
		}
		break;
	case DynamicFollowPathDemo::kFinished:
		break;
	default:
		break;
	}
}

void DynamicFollowPathDemo::Exit()
{
	if (character_boid_ != nullptr)
	{
		delete character_boid_;
		character_boid_ = nullptr;
	}
	if (path_ != nullptr)
	{
		delete path_;
		path_ = nullptr;
	}
	if (dynamic_follow_path_ != nullptr)
	{
		delete dynamic_follow_path_;
		dynamic_follow_path_ = nullptr;
	}
}

void DynamicFollowPathDemo::Draw()
{
	if (character_boid_ != nullptr)
	{
		character_boid_->Draw(true);
	}

	if (path_ != nullptr)
	{
		for (int i = 0; i < path_->waypoints_.size() - 1; i++)
		{
			ofPushMatrix();
			ofSetColor(ofColor::yellow);
			ofDrawLine(path_->waypoints_[i], path_->waypoints_[i + 1]);
			ofPopMatrix();
		}

		for (int i = 0; i < path_->waypoints_.size(); i++)
		{
			ofPushMatrix();
			ofSetColor(ofColor::yellow);
			ofTranslate(path_->waypoints_[i]);
			ofDrawCircle(0, 0, 4.0f);
			ofPopMatrix();
		}
		if (process_ == kMoving && dynamic_follow_path_->current_param_ >= 0)
		{
			ofPushMatrix();
			ofSetColor(ofColor::red);
			ofTranslate(dynamic_follow_path_->path_->GetPosition(dynamic_follow_path_->current_param_));
			ofDrawCircle(0, 0, 4.0f);
			ofPopMatrix();

			ofPushMatrix();
			ofSetColor(ofColor::blue);
			ofTranslate(dynamic_follow_path_->path_->GetPosition(dynamic_follow_path_->target_param_));
			ofDrawCircle(0, 0, 4.0f);
			ofPopMatrix();
		}

	}
	
	if (waypoints_.size() > 0)
	{

		for (int i = 0; i < waypoints_.size() - 1; i++)
		{
			ofPushMatrix();
			ofSetColor(ofColor::yellow);
			ofDrawLine(waypoints_[i], waypoints_[i + 1]);
			ofPopMatrix();
		}

		for (int i = 0; i < waypoints_.size(); i++)
		{
			ofPushMatrix();
			ofSetColor(ofColor::yellow);
			ofTranslate(waypoints_[i]);
			ofDrawCircle(0, 0, 4.0f);
			ofPopMatrix();
		}
	}
	DrawStrings();
}

void DynamicFollowPathDemo::DrawStrings()
{
	switch (process_)
	{
	case DynamicFollowPathDemo::kReady:
		break;
	case DynamicFollowPathDemo::kSetBoid:
		DrawString::Draw("Left click to create/move your character\nPress ENTER to finish this step", glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
		break;
	case DynamicFollowPathDemo::kSetPath:
		DrawString::Draw("Left click to create way points of the path\nPress ENTER to finish this step", glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
		break;
	case DynamicFollowPathDemo::kStartMove:
		break;
	case DynamicFollowPathDemo::kMoving:
		break;
	case DynamicFollowPathDemo::kFinished:
		break;
	default:
		break;
	}
}

void DynamicFollowPathDemo::keyPressed(int key)
{
	switch (process_)
	{
	case DynamicFollowPathDemo::kReady:
		break;
	case DynamicFollowPathDemo::kSetBoid:
		if (key == OF_KEY_RETURN && character_boid_ != nullptr) process_ = kSetPath;
		break;
	case DynamicFollowPathDemo::kSetPath:
		if (key == OF_KEY_RETURN && waypoints_.size() > 0)
		{
			process_ = kStartMove;
			path_ = Path::CreatePath(waypoints_, 32.0f);
			waypoints_.clear();
		}
		break;
	case DynamicFollowPathDemo::kStartMove:
		break;
	case DynamicFollowPathDemo::kMoving:
		break;
	case DynamicFollowPathDemo::kFinished:
		break;
	default:
		break;
	}
}

void DynamicFollowPathDemo::mousePressed(int x, int y, int button)
{
	if (button == 0 && !mouse_clicked)
	{
		glm::vec2 position = glm::vec2(static_cast<float>(x), static_cast<float>(y));
		mouse_clicked = true;

		switch (process_)
		{
		case DynamicFollowPathDemo::kReady:
			break;
		case DynamicFollowPathDemo::kSetBoid:
			if (character_boid_ == nullptr) character_boid_ = new Boid(position, ofDegToRad(0.0f), 8.0f, 16.0f, ofColor::green);
			else character_boid_->rigidbody_->position_ = position;
			break;
		case DynamicFollowPathDemo::kSetPath:
			waypoints_.push_back(position);
			break;
		case DynamicFollowPathDemo::kStartMove:
			break;
		case DynamicFollowPathDemo::kMoving:
			break;
		case DynamicFollowPathDemo::kFinished:
			break;
		default:
			break;
		}
	}
}

void DynamicFollowPathDemo::mouseReleased(int x, int y, int button)
{
	if (button == 0 && mouse_clicked)
	{
		mouse_clicked = false;
	}
}

