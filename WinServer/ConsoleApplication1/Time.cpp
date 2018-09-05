#include "Time.h"




Time::Time()
{
}


Time::~Time()
{
}

void Time::UpdateDeltaTime()
{
	if (Instance().lastT == nullptr)
	{
		Instance().lastT = new std::chrono::system_clock::time_point;
		return;
	}

	deltaTime = ((std::chrono::duration<float>)(std::chrono::system_clock::now() - *Instance().lastT)).count();
	*Instance().lastT = std::chrono::system_clock::now();
}

void Time::TimerStart()
{
	t = std::chrono::system_clock::now();
}

float Time::TimerEnd()
{
	return ((std::chrono::duration<float>)(std::chrono::system_clock::now() - t)).count();
}


float Time::deltaTime = 0; 
int Time::WriteTime = 0;