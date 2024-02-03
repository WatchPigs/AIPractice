#pragma once
#include "Decorator.h"

class UntilFail : public Decorator
{
protected:
	bool Run() override;
};

