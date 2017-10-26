
#include "Timer.h"
#include <GL/glut.h>

Timer::Timer()
{
	previousTime = glutGet(GLUT_ELAPSED_TIME);
	tick();
}

Timer::~Timer()
{}

// update the timer
float Timer::tick()
{
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currentTime - previousTime;
	previousTime = currentTime;
	return elapsedTime;
}

float Timer::getElapsedTimeMS()
{
	return elapsedTime;
}

float Timer::getElapsedTimeSec()
{
	return elapsedTime / 1000.0f;
}

float Timer::getCurrentTime()
{
	return currentTime;
}