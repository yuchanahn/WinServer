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
	delete inventory;
}

void InventoryManager::Write(int id)
{
	for (int i = 0; i < 30; i++) {
		if (inventory->Get(i) != 0) {
			WriteManager<fItem, fItemT> tem;
			*tem.wdata = *Item::Items[inventory->Get(i)].wdata;
			printf("Item Send name : %s\n", tem.wdata->name.c_str());
			tem.wdata->val8 = i;
			tem.Write(session::InputSession[id]->shared_from_this());
		}
	}
}

void InventoryManager::InvUpdate(fItemT * item)
{
	if (Item::Items[inventory->Get(item->id)].wdata->count != item->count) 
	{
		printf("-- item update --\n");
		UseItem(item);
	}
}

void InventoryManager::SwapSlot(std::vector<int> NewInv)
{
	printf("-- inv update --\n");
	for (int i = 0; i < 30; i++) {
		inventory->Set(NewInv[i],i);
	}
}

void InventoryManager::UseItem(fItemT * item)
{
	
	if (item->count < 1) 
	{
		Item::Items.erase(inventory->Get(item->id));
		Item::SetUserItem(inventory->Get(item->id));
		inventory->Set(item->id, 0);
	}
	else 
	{
		Item::Items[inventory->Get(item->id)].wdata->count = item->count;
		Item::SetUserItem(inventory->Get(item->id), item->count);
	}
}

fItemT * InventoryManager::Get(int index)
{
	auto index_ = inventory->Get(index);

	if (index_ != 0)
		return Item::Items[index_].wdata;
	return nullptr;
}

