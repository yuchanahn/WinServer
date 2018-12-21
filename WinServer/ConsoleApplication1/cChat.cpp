#include "COMPONENT_H.h"
#include "WriteManager.h"

cChat::~cChat()
{
}

void cChat::Start()
{
	ReadManager::ReadSome[Class::Class_fChat] = [this](PackData* data, std::shared_ptr<session> client) {
		WriteManager<fChat, fChatT> w;
		w.wdata = data->Get<fChat>();
		w.Write();
		printf("p %d : %s\n",client->id,w.wdata->str.c_str());
		delete data;
	};
}