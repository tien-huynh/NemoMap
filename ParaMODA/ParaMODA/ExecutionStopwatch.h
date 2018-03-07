#pragma once
#include <stdio.h>
#include <time.h>
//Just using clock for now 
class ExecutionStopwatch
{
public:
	ExecutionStopwatch();

	void Start();
	void Stop();
	void Reset();
	long getElapsedMilliseconds() const;
	bool isRunning();
private:

	bool _isRunning;
	clock_t _start, _stop;
};

