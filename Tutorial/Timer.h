#pragma once


// Keeps track of relapsed time
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