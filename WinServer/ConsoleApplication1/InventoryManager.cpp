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
	for (int i = 0; i < 30; i++) {
		if (inventory->Get(i) != 0) {
			WriteManager<fItem, fItemT> tem;
			*tem.wdata = *Item::Items[inventory->Get(i)].wdata;



			printf("Item Send name : %s\n", tem.wdata->name.c_str());
			tem.wdata->id = i;
			tem.Write(session::InputSession[id]->shared_from_this());
		}
	}
}

fItemT * InventoryManager::Get(int index)
{
	auto index_ = inventory->Get(index);

	if (index_ != 0)
		return Item::Items[index_].wdata;
	return nullptr;
}

