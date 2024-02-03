#include "LogString.h"
#include "ofLog.h"

LogString::LogString(std::string s) :
	s_(s)
{
}

bool LogString::Run()
{
	ofLog(OF_LOG_NOTICE, s_);
	return true;
}
