#include "COMPONENT_H.h"
#include "InventoryManager.h"




cInventory::~cInventory()
{

}

void cInventory::Start()
{
	ReadManager::ReadSome[Class::Class_fItem] = [this](PackData* data, std::shared_ptr<session> client) {
		auto item = data->Get<fItem>();
		client->inventoryManager->InvUpdate(item);
		delete data;
	};

	ReadManager::ReadSome[Class::Class_fInventory] = [this](PackData* data, std::shared_ptr<session> client) {
		auto Inv = data->Get<fInventory>();
		client->inventoryManager->SwapSlot(Inv->Slot);
		delete data;
	};
}