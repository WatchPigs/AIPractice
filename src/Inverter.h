#pragma once
#include "Decorator.h"

class Inverter : public Decorator
{
protected:
	bool Run() override;
};