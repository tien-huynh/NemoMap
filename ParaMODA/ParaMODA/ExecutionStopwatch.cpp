#include "ExecutionStopwatch.h"

ExecutionStopwatch::ExecutionStopwatch()
{
	_isRunning = false;
}

void ExecutionStopwatch::Start()
{
	_start = clock();
	_isRunning = true;
}

void ExecutionStopwatch::Stop()
{
	_stop = clock();
	_isRunning = true;
}

void ExecutionStopwatch::Reset()
{
	_isRunning = false;
}

long ExecutionStopwatch::getElapsedMilliseconds() const
{
	return long(_stop - _start);
}

bool ExecutionStopwatch::isRunning()
{
	return _isRunning;
}