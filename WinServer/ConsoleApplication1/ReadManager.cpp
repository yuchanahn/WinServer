#include "ReadManager.h"
#include "Base_generated.h"
#include "ClientSession.h"

ReadManager::ReadManager()
{
}

ReadManager::~ReadManager()
{
}

void ReadManager::Read(char data_[1024], size_t length ,std::shared_ptr<session> Client)
{
	PackData * packData = new PackData(length);
	memcpy(packData->data, data_, length);

	auto data(GetBase(packData->data));

	if (ReadSome.find(data->cType()) == ReadSome.end()) {
		printf("잘못된 패킷 받음. type num : %d\n", data->cType());
		return;
	}

	ReadSome[data->cType()](packData, Client->shared_from_this());
}

std::map<Class, std::function<void(PackData*, std::shared_ptr<session>) >> ReadManager::ReadSome;

Base * PackData::m_GetBase(char * data_)
{
	return (Base*)GetBase(data_);
}
