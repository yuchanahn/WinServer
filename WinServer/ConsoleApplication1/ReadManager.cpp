#include "ReadManager.h"
#include "Base_generated.h"
#include "ClientSession.h"




ReadManager::ReadManager()
{

}

ReadManager::~ReadManager()
{
}






void ReadManager::Read(char data_[1024], size_t length, std::shared_ptr<session> Client)
{
	PackData * packData = new PackData(length);
	memcpy(packData->data, data_, length);

	int size = packData->Get<fheader>()->PacketSize;

	int startidx = 24;

	delete packData;

	packData = new PackData(size);
	memcpy(packData->data, &data_[startidx], size);

	auto data(GetBase(packData->data));

	if (ReadSome.find(data->cType()) == ReadSome.end()) {
		printf("잘못된 패킷 받음. type num : %d\n", data->cType());
		return;
	}

	ReadSome[data->cType()](packData, Client->shared_from_this());
	int faenalSize = size + startidx;
	if (faenalSize < length) {
		printf("패킷이 뭉쳐서옴. szie : %d\n", length);
		Read(&data_[faenalSize], length - faenalSize, Client);
	}
}

int ReadManager::buffToInteger(char * buffer)
{
	int a = static_cast<int>(static_cast<unsigned char>(buffer[0]) << 24 |
		static_cast<unsigned char>(buffer[1]) << 16 |
		static_cast<unsigned char>(buffer[2]) << 8 |
		static_cast<unsigned char>(buffer[3]));
	return a;
}
std::map<Class, std::function<void(PackData*, std::shared_ptr<session>) >> ReadManager::ReadSome;


Base * PackData::m_GetBase(char * data_)
{
	return (Base*)GetBase(data_);
}
