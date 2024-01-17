#include "PathfindingAStarDemo.h"
#include "DrawString.h"

PathfindingAStarDemo::PathfindingAStarDemo() :
	tile_graph_(nullptr), start_node_(nullptr), end_node_(nullptr), heuristic_(nullptr), a_star_thread_(nullptr), process_(kReady)
{
}

void PathfindingAStarDemo::Setup()
{
	tile_graph_ = new TileGraph(32, glm::vec2(ofGetWidth(), ofGetHeight()));

	heuristic_ = new Heuristic(Heuristic::kManhattanDistance);

	a_star_thread_ = new AStarThread(5);
}

void PathfindingAStarDemo::Update()
{
	switch (process_)
	{
	case PathfindingAStarDemo::kReady:
		break;
	case PathfindingAStarDemo::kSetObstacles:
		break;
	case PathfindingAStarDemo::kSetStart:
		break;
	case PathfindingAStarDemo::kSetEnd:
		break;
	case PathfindingAStarDemo::kStartProcess:
		process_ = kProcessing;
		a_star_thread_->Init(tile_graph_, start_node_, end_node_, heuristic_);
		a_star_thread_->startThread();
		break;
	case PathfindingAStarDemo::kProcessing:
		if (a_star_thread_->finished_)
		{
			process_ = kFinished;
			SetPathNodes(a_star_thread_->result_);
		}
		break;
	case PathfindingAStarDemo::kFinished:
		break;
	default:
		break;
	}
}

void PathfindingAStarDemo::Exit()
{
	if (a_star_thread_ != nullptr)
	{
		a_star_thread_->stopThread();
		delete a_star_thread_;
		a_star_thread_ = nullptr;
	}
	if (tile_graph_ != nullptr)
	{
		delete tile_graph_;
		tile_graph_ = nullptr;
	}
	if (start_node_ != nullptr) start_node_ = nullptr;
	if (end_node_ != nullptr) end_node_ = nullptr;
	if (heuristic_ != nullptr)
	{
		delete heuristic_;
		heuristic_ = nullptr;
	}
}

void PathfindingAStarDemo::Draw()
{
	for (auto node : tile_graph_->nodes_)
	{
		TileNode* tile_node = dynamic_cast<TileNode*>(node);
		if (tile_node != nullptr)
		{
			ofPushMatrix();

			ofColor color;
			switch (tile_node->status)
			{
			case Node::kUnvisited:
				color = ofColor::white;
				color.a = 63;
				break;
			case Node::kOpen:
				color = ofColor::green;
				color.a = 127;
				break;
			case Node::kClosed:
				color = ofColor::green;
				color.a = 63;
				break;
			case Node::kPath:
				color = ofColor::red;
				break;
			default:
				break;
			}

			if (tile_node == start_node_) color = ofColor::brown;
			if (tile_node == end_node_) color = ofColor::orange;

			ofSetColor(color);

			ofTranslate(tile_graph_->GetNodePosition(tile_node));

			ofDrawRectangle(0.0f, 0.0f, tile_graph_->tile_size_, tile_graph_->tile_size_);

			ofPopMatrix();
		}
	}
	DrawStrings();
}

void PathfindingAStarDemo::SetPathNodes(std::list<Connection*> result)
{
	for (Connection* connection : result)
	{
		if (connection->from_node_ != start_node_) connection->from_node_->status = Node::kPath;
	}
}

void PathfindingAStarDemo::DrawStrings()
{
	switch (process_)
	{
	case PathfindingAStarDemo::kReady:
		break;
	case PathfindingAStarDemo::kSetObstacles:
		DrawString::Draw("Left click anywhere to set obstacles\nPress ENTER to finish this step", glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
		break;
	case PathfindingAStarDemo::kSetStart:
		DrawString::Draw("Left click anywhere to set start position", glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
		break;
	case PathfindingAStarDemo::kSetEnd:
		DrawString::Draw("Left click anywhere to set end position", glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.25f), DrawString::kHorizontalCenter, DrawString::VerticalAlign::kVerticalTop, ofColor::white);
		break;
	case PathfindingAStarDemo::kStartProcess:
		break;
	case PathfindingAStarDemo::kProcessing:
		break;
	case PathfindingAStarDemo::kFinished:
		break;
	default:
		break;
	}
}

void PathfindingAStarDemo::keyPressed(int key)
{
	switch (process_)
	{
	case PathfindingAStarDemo::kReady:
		break;
	case PathfindingAStarDemo::kSetObstacles:
		if (key == OF_KEY_RETURN) process_ = kSetStart;
		break;
	case PathfindingAStarDemo::kSetStart:
		break;
	case PathfindingAStarDemo::kSetEnd:
		break;
	case PathfindingAStarDemo::kStartProcess:
		break;
	case PathfindingAStarDemo::kProcessing:
		break;
	case PathfindingAStarDemo::kFinished:
		break;
	default:
		break;
	}
}

void PathfindingAStarDemo::mousePressed(int x, int y, int button)
{
	if (button == 0)
	{
		glm::vec2 position = glm::vec2(static_cast<float>(x), static_cast<float>(y));
		TileNode* node = tile_graph_->GetNodeOnPosition(position);
		switch (process_)
		{
		case PathfindingAStarDemo::kReady:
			break;
		case PathfindingAStarDemo::kSetObstacles:
			if (node != nullptr) tile_graph_->RemoveNode(node);
			break;
		case PathfindingAStarDemo::kSetStart:
			if (node != nullptr)
			{
				start_node_ = node;
				process_ = kSetEnd;
			}
			break;
		case PathfindingAStarDemo::kSetEnd:
			if (node != nullptr && node != start_node_)
			{
				end_node_ = node;
				process_ = kStartProcess;
			}
			break;
		case PathfindingAStarDemo::kStartProcess:
			break;
		case PathfindingAStarDemo::kProcessing:
			break;
		case PathfindingAStarDemo::kFinished:
			break;
		default:
			break;
		}

	}
}

