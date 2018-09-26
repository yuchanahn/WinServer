#include "InventoryManager.h"
#include "Inventory.h"
#include "Item.h"
#include "WriteManager.h"

InventoryManager::InventoryManager(int id)
{
	inventory = new Inventory(id);
	playerID = id;
	Write();
}


InventoryManager::~InventoryManager()
{
	delete inventory;
}

void InventoryManager::Write()
{
	for (int i = 0; i < 30; i++) {
		if (inventory->Get(i) != 0) {
			writefItem(inventory->Get(i), i);
		}
	}
}

void InventoryManager::WriteNewItem(int id)
{
	for (int i = 0; i < 30; i++) {
		if (inventory->Get(i) == 0) {
			writefItem(id, i);
			inventory->Set(id, i);
			return;
		}
	}
}

void InventoryManager::InvUpdate(fItemT * item)
{
	if (item->type == -1)
	{
		int itemid = Item::CreateItem(item->id,item->count);
		WriteNewItem(itemid);
	}
	else if (Item::Items[item->id].wdata->count != item->count)
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
		Item::Items.erase(item->id);
		Item::SetUserItem(item->id);
		inventory->Set(inventory->GetSlotNum(item->id), 0);
	}
	else 
	{
		Item::Items[item->id].wdata->count = item->count;
		Item::SetUserItem(item->id, item->count);
	}
}

fItemT * InventoryManager::Get(int index)
{
	auto index_ = inventory->Get(index);

	if (index_ != 0)
		return Item::Items[index_].wdata;
	return nullptr;
}

void InventoryManager::writefItem(int id, int slotNum) {
	WriteManager<fItem, fItemT> tem;
	*tem.wdata = *Item::Items[id].wdata;
	tem.wdata->id = id;
	printf("Item[id] Send name : %s\n", Item::Items[id].wdata->name.c_str());
	printf("Item Send name : %s\n", tem.wdata->name.c_str());
	printf("id : %d, slotnum : %d\n", id, slotNum);
	tem.wdata->val8 = slotNum;
	tem.Write(session::InputSession[playerID]->shared_from_this());
}