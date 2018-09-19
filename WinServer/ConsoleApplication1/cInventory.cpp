#include "COMPONENT_H.h"





cInventory::~cInventory()
{

}

void cInventory::Start()
{
	ReadManager::ReadSome[Class::Class_fItem] = [this](PackData* data, std::shared_ptr<session> client) {
		auto item = data->Get<fItem>();


		delete data;
	};
}