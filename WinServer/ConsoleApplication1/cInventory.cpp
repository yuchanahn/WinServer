#include "COMPONENT_H.h"
#include "InventoryManager.h"




cInventory::~cInventory()
{

}

void cInventory::Start()
{
	ReadManager::ReadSome[Class::Class_fItem] = [this](PackData* data, std::shared_ptr<session> client) {
		auto item = data->Get<fItem>();
		if(client->inventoryManager != nullptr)
			client->inventoryManager->InvUpdate(item);
		delete data;
	};

	ReadManager::ReadSome[Class::Class_fInventory] = [this](PackData* data, std::shared_ptr<session> client) {
		auto Inv = data->Get<fInventory>();
		if (client->inventoryManager != nullptr)
			client->inventoryManager->SwapSlot(Inv->Slot);
		delete data;
	};
}