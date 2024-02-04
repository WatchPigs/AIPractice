#include "ofApp.h"
#include "DrawString.h"

void ofApp::CleanUp()
{
	switch (demo_selection_)
	{
	case kTestDemo:
		test_demo_->Exit();
		delete test_demo_;
		test_demo_ = nullptr;
		break;
	case kNoneDemo:
		break;
	case kKinematicArriveDemo:
		kinematic_arrive_demo_->Exit();
		delete kinematic_arrive_demo_;
		kinematic_arrive_demo_ = nullptr;
		break;
	case kDynamicArriveVSSeekDemo:
		dynamic_arrive_vs_seek_demo_->Exit();
		delete dynamic_arrive_vs_seek_demo_;
		dynamic_arrive_vs_seek_demo_ = nullptr;
		break;
	case kDynamicPursueVSSeekDemo:
		dynamic_pursue_vs_seek_demo_->Exit();
		delete dynamic_pursue_vs_seek_demo_;
		dynamic_pursue_vs_seek_demo_ = nullptr;
		break;
	case kDynamicFaceDemo:
		dynamic_face_demo_->Exit();
		delete dynamic_face_demo_;
		dynamic_face_demo_ = nullptr;
		break;
	case kDynamicWanderDemo:
		dynamic_wander_demo_->Exit();
		delete dynamic_wander_demo_;
		dynamic_wander_demo_ = nullptr;
		break;
	case kDynamicFlockingDemo:
		dynamic_flocking_demo_->Exit();
		delete dynamic_flocking_demo_;
		dynamic_flocking_demo_ = nullptr;
		break;
	case kDynamicFollowPathDemo:
		dynamic_follow_path_demo_->Exit();
		delete dynamic_follow_path_demo_;
		dynamic_follow_path_demo_ = nullptr;
		break;
	case kPathfindingDijkstraDemo:
		pathfinding_dijkstra_demo_->Exit();
		delete pathfinding_dijkstra_demo_;
		pathfinding_dijkstra_demo_ = nullptr;
		break;
	case kPathfindingAStarDemo:
		pathfinding_astar_demo_->Exit();
		delete pathfinding_astar_demo_;
		pathfinding_astar_demo_ = nullptr;
		break;
	case kBehaviorTreeDemo:
		behavior_tree_demo_->Exit();
		delete behavior_tree_demo_;
		behavior_tree_demo_ = nullptr;
		break;
	default:
		break;
	}
}

void ofApp::DrawStrings()
{
	ofPushMatrix();
	if (!demo_selected_) DrawString::Draw(main_menu_string_, glm::vec2(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalCenter, ofColor::white);
	if (demo_selected_) DrawString::Draw("Press Q to main menu", glm::vec2(ofGetWidth(), 0.0f), DrawString::kHorizontalRight, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
	if (demo_selected_ && !begin_move_) DrawString::Draw("Press space to start", glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::setup(){
	
}

//--------------------------------------------------------------
void ofApp::update(){
	if (begin_move_)
	{
		switch (demo_selection_)
		{
		case kTestDemo:
			test_demo_->Update();
			break;
		case kNoneDemo:
			break;
		case kKinematicArriveDemo:
			kinematic_arrive_demo_->Update();
			break;
		case kDynamicArriveVSSeekDemo:
			dynamic_arrive_vs_seek_demo_->Update();
			break;
		case kDynamicPursueVSSeekDemo:
			dynamic_pursue_vs_seek_demo_->Update();
			break;
		case kDynamicFaceDemo:
			dynamic_face_demo_->Update();
			break;
		case kDynamicWanderDemo:
			dynamic_wander_demo_->Update();
			break;
		case kDynamicFlockingDemo:
			dynamic_flocking_demo_->Update();
			break;
		case kDynamicFollowPathDemo:
			dynamic_follow_path_demo_->Update();
			break;
		case kPathfindingDijkstraDemo:
			pathfinding_dijkstra_demo_->Update();
			break;
		case kPathfindingAStarDemo:
			pathfinding_astar_demo_->Update();
			break;
		case kBehaviorTreeDemo:
			behavior_tree_demo_->Update();
			break;
		default:
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
	switch (demo_selection_)
	{
	case kTestDemo:
		test_demo_->Draw();
		break;
	case kNoneDemo:
		break;
	case kKinematicArriveDemo:
		kinematic_arrive_demo_->Draw();
		break;
	case kDynamicArriveVSSeekDemo:
		dynamic_arrive_vs_seek_demo_->Draw();
		break;
	case kDynamicPursueVSSeekDemo:
		dynamic_pursue_vs_seek_demo_->Draw();
		break;
	case kDynamicFaceDemo:
		dynamic_face_demo_->Draw();
		break;
	case kDynamicWanderDemo:
		dynamic_wander_demo_->Draw();
		break;
	case kDynamicFlockingDemo:
		dynamic_flocking_demo_->Draw();
		break;
	case kDynamicFollowPathDemo:
		dynamic_follow_path_demo_->Draw();
		break;
	case kPathfindingDijkstraDemo:
		pathfinding_dijkstra_demo_->Draw();
		break;
	case kPathfindingAStarDemo:
		pathfinding_astar_demo_->Draw();
		break;
	case kBehaviorTreeDemo:
		behavior_tree_demo_->Draw();
		break;
	default:
		break;
	}

	DrawStrings();
}

//--------------------------------------------------------------
void ofApp::exit() {
	CleanUp();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (!demo_selected_)
	{
		if (key == 'T' || key == 't')
		{
			demo_selected_ = true;
			demo_selection_ = kTestDemo;
			test_demo_ = new TestDemo();
			test_demo_->Setup();
		}
		if (key == '1')
		{
			demo_selected_ = true;
			demo_selection_ = kKinematicArriveDemo;
			kinematic_arrive_demo_ = new KinematicArriveDemo();
			kinematic_arrive_demo_->Setup();
		}
		if (key == '2')
		{
			demo_selected_ = true;
			demo_selection_ = kDynamicArriveVSSeekDemo;
			dynamic_arrive_vs_seek_demo_ = new DynamicArriveVSSeekDemo();
			dynamic_arrive_vs_seek_demo_->Setup();
		}
		if (key == '3')
		{
			demo_selected_ = true;
			demo_selection_ = kDynamicPursueVSSeekDemo;
			dynamic_pursue_vs_seek_demo_ = new DynamicPursueVSSeekkDemo();
			dynamic_pursue_vs_seek_demo_->Setup();
		}
		if (key == '4')
		{
			demo_selected_ = true;
			demo_selection_ = kDynamicFaceDemo;
			dynamic_face_demo_ = new DynamicFaceDemo();
			dynamic_face_demo_->Setup();
		}
		if (key == '5')
		{
			demo_selected_ = true;
			demo_selection_ = kDynamicWanderDemo;
			dynamic_wander_demo_ = new DynamicWanderDemo();
			dynamic_wander_demo_->Setup();
		}
		if (key == '6')
		{
			demo_selected_ = true;
			demo_selection_ = kDynamicFlockingDemo;
			dynamic_flocking_demo_ = new DynamicFlockingDemo();
			dynamic_flocking_demo_->Setup();
		}
		if (key == '7')
		{
			demo_selected_ = true;
			demo_selection_ = kDynamicFollowPathDemo;
			dynamic_follow_path_demo_ = new DynamicFollowPathDemo();
			dynamic_follow_path_demo_->Setup();
		}
		if (key == '8')
		{
			demo_selected_ = true;
			demo_selection_ = kPathfindingDijkstraDemo;
			pathfinding_dijkstra_demo_ = new PathfindingDijkstraDemo();
			pathfinding_dijkstra_demo_->Setup();
		}
		if (key == '9')
		{
			demo_selected_ = true;
			demo_selection_ = kPathfindingAStarDemo;
			pathfinding_astar_demo_ = new PathfindingAStarDemo();
			pathfinding_astar_demo_->Setup();
		}
		if (key == '0')
		{
			demo_selected_ = true;
			demo_selection_ = kBehaviorTreeDemo;
			behavior_tree_demo_ = new BehaviorTreeDemo();
			behavior_tree_demo_->Setup();
		}
	}
	if (demo_selected_ && !begin_move_)
	{
		if (key == ' ')
		{
			begin_move_ = true;

			switch (demo_selection_)
			{
			case ofApp::kNoneDemo:
				break;
			case ofApp::kKinematicArriveDemo:
				break;
			case ofApp::kDynamicArriveVSSeekDemo:
				break;
			case ofApp::kDynamicPursueVSSeekDemo:
				break;
			case ofApp::kDynamicFaceDemo:
				break;
			case ofApp::kDynamicWanderDemo:
				break;
			case ofApp::kDynamicFlockingDemo:
				break;
			case ofApp::kDynamicFollowPathDemo:
				dynamic_follow_path_demo_->process_ = DynamicFollowPathDemo::kSetBoid;
				break;
			case ofApp::kPathfindingDijkstraDemo:
				pathfinding_dijkstra_demo_->process_ = PathfindingDijkstraDemo::kSetObstacles;
				break;
			case ofApp::kPathfindingAStarDemo:
				pathfinding_astar_demo_->process_ = PathfindingAStarDemo::kSetObstacles;
				break;
			case ofApp::kBehaviorTreeDemo:
				behavior_tree_demo_->process_ = BehaviorTreeDemo::kSetChargingStations;
				break;
			default:
				break;
			}
		}
	}

	if (demo_selected_)
	{
		if (key == 'q' || key == 'Q')
		{
			begin_move_ = false;
			CleanUp();
			demo_selection_ = kNoneDemo;
			demo_selected_ = false;
		}
	}

	if (demo_selected_ && begin_move_)
	{
		switch (demo_selection_)
		{
		case kTestDemo:
			test_demo_->keyPressed(key);
		case kNoneDemo:
			break;
		case kKinematicArriveDemo:
			break;
		case kDynamicArriveVSSeekDemo:
			break;
		case kDynamicPursueVSSeekDemo:
			break;
		case kDynamicFaceDemo:
			break;
		case kDynamicWanderDemo:
			break;
		case kDynamicFlockingDemo:
			break;
		case kDynamicFollowPathDemo:
			dynamic_follow_path_demo_->keyPressed(key);
			break;
		case kPathfindingDijkstraDemo:
			pathfinding_dijkstra_demo_->keyPressed(key);
			break;
		case kPathfindingAStarDemo:
			pathfinding_astar_demo_->keyPressed(key);
			break;
		case kBehaviorTreeDemo:
			behavior_tree_demo_->keyPressed(key);
		default:
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (demo_selected_ && begin_move_)
	{
		switch (demo_selection_)
		{
		case ofApp::kNoneDemo:
			break;
		case ofApp::kKinematicArriveDemo:
			break;
		case ofApp::kDynamicArriveVSSeekDemo:
			break;
		case ofApp::kDynamicPursueVSSeekDemo:
			break;
		case ofApp::kDynamicFaceDemo:
			break;
		case ofApp::kDynamicWanderDemo:
			break;
		case ofApp::kDynamicFlockingDemo:
			break;
		case ofApp::kDynamicFollowPathDemo:
			break;
		case ofApp::kPathfindingDijkstraDemo:
			break;
		case ofApp::kPathfindingAStarDemo:
			break;
		case ofApp::kBehaviorTreeDemo:
			break;
		default:
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (demo_selected_ && begin_move_)
	{
		switch (demo_selection_)
		{
		case ofApp::kNoneDemo:
			break;
		case ofApp::kKinematicArriveDemo:
			break;
		case ofApp::kDynamicArriveVSSeekDemo:
			break;
		case ofApp::kDynamicPursueVSSeekDemo:
			break;
		case ofApp::kDynamicFaceDemo:
			break;
		case ofApp::kDynamicWanderDemo:
			break;
		case ofApp::kDynamicFlockingDemo:
			break;
		case ofApp::kDynamicFollowPathDemo:
			dynamic_follow_path_demo_->mousePressed(x, y, button);
			break;
		case ofApp::kPathfindingDijkstraDemo:
			pathfinding_dijkstra_demo_->mousePressed(x, y, button);
			break;
		case ofApp::kPathfindingAStarDemo:
			pathfinding_astar_demo_->mousePressed(x, y, button);
			break;
		case ofApp::kBehaviorTreeDemo:
			behavior_tree_demo_->mousePressed(x, y, button);
			break;
		default:
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (demo_selected_ && begin_move_)
	{
		switch (demo_selection_)
		{
		case ofApp::kNoneDemo:
			break;
		case ofApp::kKinematicArriveDemo:
			break;
		case ofApp::kDynamicArriveVSSeekDemo:
			break;
		case ofApp::kDynamicPursueVSSeekDemo:
			break;
		case ofApp::kDynamicFaceDemo:
			break;
		case ofApp::kDynamicWanderDemo:
			break;
		case ofApp::kDynamicFollowPathDemo:
			dynamic_follow_path_demo_->mouseReleased(x, y, button);
			break;
		case ofApp::kDynamicFlockingDemo:
			break;
		case ofApp::kPathfindingDijkstraDemo:
			break;
		case ofApp::kPathfindingAStarDemo:
			break;
		case ofApp::kBehaviorTreeDemo:
			behavior_tree_demo_->mouseReleased(x, y, button);
			break;
		default:
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
