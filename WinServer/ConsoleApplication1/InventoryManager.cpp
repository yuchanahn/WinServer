#include "InventoryManager.h"
#include "Inventory.h"
#include "Item.h"
#include "WriteManager.h"

InventoryManager::InventoryManager(int id)
{
	inventory = new Inventory(id);
	Write(id);
}


InventoryManager::~InventoryManager()
{
}

void InventoryManager::Write(int id)
{
	WriteManager<fInventory, fInventoryT> Inven;
	Inven.wdata->cType = Class::Class_fInventory;
	Inven.wdata->Slot.resize(30);

	for (int i = 0; i > 30; i++) {
		Inven.wdata->Slot[i] = inventory->Get(i);
	}
	Inven.Write(session::InputSession[id]->shared_from_this());
}

fItemT * InventoryManager::Get(int index)
{
	auto index_ = inventory->Get(index);

	if(index_ != 0)
		return Item::Items[index_].wdata;
	return nullptr;
}
