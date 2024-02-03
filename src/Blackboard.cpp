#include "Blackboard.h"
#include "ofLog.h"

Blackboard::Blackboard() :
	in_cleaning_up_(false)
{

}

Blackboard::~Blackboard()
{
	
}

void Blackboard::SafeCleanUp()
{
	in_cleaning_up_ = true;
	std::unique_lock<std::shared_mutex> lock(mtx_bb_in_use_);
}
