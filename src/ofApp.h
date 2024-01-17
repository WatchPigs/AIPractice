#pragma once

#include "ofMain.h"
#include <string>
#include "KinematicArriveDemo.h"
#include "DynamicArriveVSSeekDemo.h"
#include "DynamicPursueVSSeekDemo.h"
#include "DynamicFaceDemo.h"
#include "DynamicWanderDemo.h"
#include "DynamicFlockingDemo.h"
#include "PathfindingDijkstraDemo.h"
#include "PathfindingAStarDemo.h"

class ofApp : public ofBaseApp{

	public:

		string main_menu_string_ = "Press numbers to choose:\n[Physics & Movement & Steering Behaviors]\n1: Kinematic Arrive Demo\n2: Dynamic Arrive VS Seek Demo\n3: Dynamic Pursue VS Seek Demo\n4: Dynamic Face Demo\n5: Dynamic Wander Demo\n6: Dynamic Flocking Demo\n[Pathfinding]\n7: Pathfinding Dijkstra Demo\n8: Pathfinding AStar Demo";

		enum DemoSelector
		{
			kNoneDemo = 0,
			kKinematicArriveDemo = 1,
			kDynamicArriveVSSeekDemo = 2,
			kDynamicPursueVSSeekDemo = 3,
			kDynamicFaceDemo = 4,
			kDynamicWanderDemo = 5,
			kDynamicFlockingDemo = 6,
			kPathfindingDijkstraDemo = 7,
			kPathfindingAStarDemo = 8,
		};

		bool demo_selected_ = false;
		DemoSelector demo_selection_ = kNoneDemo;
		
		bool begin_move_ = false;

		KinematicArriveDemo* kinematic_arrive_demo_;
		DynamicArriveVSSeekDemo* dynamic_arrive_vs_seek_demo_;
		DynamicPursueVSSeekkDemo* dynamic_pursue_vs_seek_demo_;
		DynamicFaceDemo* dynamic_face_demo_;
		DynamicWanderDemo* dynamic_wander_demo_;
		DynamicFlockingDemo* dynamic_flocking_demo_;
		PathfindingDijkstraDemo* pathfinding_dijkstra_demo_;
		PathfindingAStarDemo* pathfinding_astar_demo_;


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
