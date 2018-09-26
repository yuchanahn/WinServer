#include "COMPONENT_H.h"
#include <thread>

cServerFPS::~cServerFPS()
{
}

void cServerFPS::Update()
{
	dt += Time::deltaTime;
	fps++;
	if (dt > 1.0f) {
		//printf("Server FPS : %d | WriteTime : %d\n", fps, Time::WriteTime);
		dt	= 0;
		fps	= 0;
		Time::WriteTime = 0;

		//printf("thread ID : %d\n", std::this_thread::get_id());
	}
}