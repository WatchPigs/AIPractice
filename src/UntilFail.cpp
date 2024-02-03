#include "UntilFail.h"

bool UntilFail::Run()
{
	while (isThreadRunning())
	{
		if (child_ == nullptr) return false;
		child_->startThread();
		child_->waitForThread(false);
		if (!isThreadRunning()) return false;
		if (!child_->result_) break;
	}
	return true;
}
