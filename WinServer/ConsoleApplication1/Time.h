#pragma once
#include <chrono>

class Time
{
	std::chrono::system_clock::time_point * lastT = nullptr;

	std::chrono::system_clock::time_point t;

public:
	static float deltaTime;
	static int WriteTime;

	static Time& Instance() {
		static Time t;
		return t;
	}
	Time();
	~Time();

	static void UpdateDeltaTime();





	void TimerStart();
	float TimerEnd();
};

