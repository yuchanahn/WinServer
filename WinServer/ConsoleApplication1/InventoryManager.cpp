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
			auto ItemKey = inventory->Get(i);
			writefItem(Item::Items[ItemKey].wdata, ItemKey);
		}
	}
}

void InventoryManager::WriteNewItem(int ItemKey)
{
	for (int i = 0; i < 30; i++) {
		if (inventory->Get(i) == 0) {
			inventory->Set(ItemKey, i);
			writefItem(Item::Items[ItemKey].wdata, ItemKey);
			return;
		}
	}
}

void InventoryManager::InvUpdate(fItemT * item)
{
	if (item->type == -1)	printf("ITEM UPDATE[+]\n"); 
	else					printf("ITEM UPDATE[-]\n");


	if (item->type == -1) { // id-> Code
		for (int i = 0; i < 30; i++) {
			if (inventory->Get(i) == 0) continue;
			if (Item::Items[inventory->Get(i)].wdata->id == item->id) {
				Item::Items[inventory->Get(i)].wdata->count += item->count;
				ItemCountUpdate(Item::Items[inventory->Get(i)].wdata, inventory->Get(i));
				writefItem(Item::Items[inventory->Get(i)].wdata, inventory->Get(i));
				return;
			}
		}
		printf("CREATE ITEM\n");
		int itemid = Item::CreateItem(item->id, item->count);
		WriteNewItem(itemid);
	}
	else {					// id-> ItemKey
		Item::Items[item->id].wdata->count -= item->count;
		ItemCountUpdate(item, item->id);
		return;
	}


}

void InventoryManager::SwapSlot(std::vector<int> NewInv)
{
	printf("INVENTORY UPDATE\n");
	for (int i = 0; i < 30; i++) {
		inventory->Set(NewInv[i], i);
	}
}

void InventoryManager::ItemCountUpdate(fItemT * item, int id)
{
	if (Item::Items[id].wdata->count < 1)
	{
		Item::Items.erase(id);
		Item::SetUserItem(id);
		inventory->Set(0, inventory->GetSlotNum(id));
	}
	else
	{
		Item::SetUserItem(id, item->count);
	}
}


fItemT * InventoryManager::Get(int index)
{
	auto index_ = inventory->Get(index);

	if (index_ != 0)
		return Item::Items[index_].wdata;
	return nullptr;
}


void InventoryManager::writefItem(fItemT * item, int ItemKey)
{
	WriteManager<fItem, fItemT> tem;
	*tem.wdata = *item;
	tem.wdata->id = ItemKey;
	printf(">> name : %s | ", tem.wdata->name.c_str());
	printf("id : %d | slotnum : %d | Count : %d\n", ItemKey, inventory->GetSlotNum(ItemKey), item->count);
	tem.wdata->val8 = inventory->GetSlotNum(ItemKey);
	if(session::InputSession.find(playerID)!= session::InputSession.end())
		tem.Write(session::InputSession[playerID]->shared_from_this());
}
