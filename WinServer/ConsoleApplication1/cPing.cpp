#include "COMPONENT_H.h"
#include <thread>

cPing::~cPing()
{
}

void cPing::Start()
{
	ReadManager::ReadSome[Class::Class_ping] = [this](PackData* data, std::shared_ptr<session> client) {
		Time timer;
		timer.TimerStart();
		data->Get<ping, pingT>(wdata);
		Write(client);
		delete data;
		printf("%lf\n" ,timer.TimerEnd());
	};
}
