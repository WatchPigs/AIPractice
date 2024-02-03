#include "Inverter.h"

bool Inverter::Run()
{
	if (child_ == nullptr) return false;
	child_->startThread();
	child_->waitForThread(false);
	if (!isThreadRunning()) return false;
	return !child_->result_;
}
