#pragma once

#include "ofMain.h"
#include <string>
#include "TestDemo.h"
#include "KinematicArriveDemo.h"
#include "DynamicArriveVSSeekDemo.h"
#include "DynamicPursueVSSeekDemo.h"
#include "DynamicFaceDemo.h"
#include "DynamicWanderDemo.h"
#include "DynamicFlockingDemo.h"
#include "DynamicFollowPathDemo.h"
#include "PathfindingDijkstraDemo.h"
#include "PathfindingAStarDemo.h"
#include "BehaviorTreeDemo.h"

class ofApp : public ofBaseApp{

	public:

		string main_menu_string_ = "Press number keys to choose:\n\n[Physics & Movement & Steering Behaviors]\n1: Kinematic Arrive Demo\n2: Dynamic Arrive VS Seek Demo\n3: Dynamic Pursue VS Seek Demo\n4: Dynamic Face Demo\n5: Dynamic Wander Demo\n6: Dynamic Flocking Demo\n7: Dynamic Follow Path Demo\n\n[Pathfinding]\n8: Pathfinding Dijkstra Demo\n9: Pathfinding AStar Demo\n\n[Decision Making]\n0: Behavior Tree Demo (Janitor Robot)";

		enum DemoSelector
		{
			kTestDemo = -1,
			kNoneDemo = 0,
			kKinematicArriveDemo = 1,
			kDynamicArriveVSSeekDemo = 2,
			kDynamicPursueVSSeekDemo = 3,
			kDynamicFaceDemo = 4,
			kDynamicWanderDemo = 5,
			kDynamicFlockingDemo = 6,
			kDynamicFollowPathDemo = 7,
			kPathfindingDijkstraDemo = 8,
			kPathfindingAStarDemo = 9,
			kBehaviorTreeDemo = 10,
		};

		bool demo_selected_ = false;
		DemoSelector demo_selection_ = kNoneDemo;
		
		bool begin_move_ = false;

		TestDemo* test_demo_;
		KinematicArriveDemo* kinematic_arrive_demo_;
		DynamicArriveVSSeekDemo* dynamic_arrive_vs_seek_demo_;
		DynamicPursueVSSeekkDemo* dynamic_pursue_vs_seek_demo_;
		DynamicFaceDemo* dynamic_face_demo_;
		DynamicWanderDemo* dynamic_wander_demo_;
		DynamicFlockingDemo* dynamic_flocking_demo_;
		DynamicFollowPathDemo* dynamic_follow_path_demo_;
		PathfindingDijkstraDemo* pathfinding_dijkstra_demo_;
		PathfindingAStarDemo* pathfinding_astar_demo_;
		BehaviorTreeDemo* behavior_tree_demo_;


		void CleanUp();
		void DrawStrings();

		
//--------------------------------------------
// 
// OpenFrameworks default members
// 
//--------------------------------------------
		
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
