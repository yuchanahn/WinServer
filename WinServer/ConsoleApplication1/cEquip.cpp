#include "COMPONENT_H.h"



cEquip::~cEquip()
{
}



void cInventory::Start()
{
	ReadManager::ReadSome[Class::Class_fInventory] = [this](PackData* data, std::shared_ptr<session> client) {
		auto Inv = data->Get<fInventory>();
		if (client->inventoryManager != nullptr)
			client->inventoryManager->SwapSlot(Inv->Slot);
		delete data;
	};
}