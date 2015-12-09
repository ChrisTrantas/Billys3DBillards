#include "Time.hpp"
#include <GLFW/glfw3.h>

double Time::_startTime;
double Time::_currFrame;
double Time::_lastFrame;

// Start keeping track of time
void Time::Start()
{
    _startTime = _currFrame = _lastFrame = glfwGetTime();
}

// Update time values
void Time::Update()
{
    _lastFrame = _currFrame;
    _currFrame = glfwGetTime();
}

// Get the elapsed time
float Time::GetElapsedTime()
{
    return static_cast<float>( _currFrame - _lastFrame );
}

// Get the total running time
float Time::GetTotalTime()
{
    return static_cast<float>( _currFrame - _startTime );
}
