#pragma once


// Keeps track of elapsed time
class Timer
{
public:
	Timer();
	~Timer();

	float tick();
	float getElapsedTimeMS();
	float getElapsedTimeSec();
	float getCurrentTime();

private:
	float currentTime, previousTime, elapsedTime;
};