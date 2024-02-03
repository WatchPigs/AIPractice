#pragma once
#include "BehaviorTree.h"
#include "Rigidbody.h"

class BehaviorTreeJR : public BehaviorTree
{
public:
	BehaviorTreeJR(Rigidbody* character_rb);
	BehaviorTreeJR() = delete;
};

