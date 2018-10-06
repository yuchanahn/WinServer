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
	if (item->type == -1) {
		printf("**** ITEM [+] ****\n");
	}
	else
		printf("**** ITEM [-] ****\n");


	if (item->type == -1) { // id-> Code
		for (int i = 0; i < 30; i++) {
			if (inventory->Get(i) == 0) continue;
			if (Item::Items[inventory->Get(i)].wdata->id == item->id) {
				item->count += Item::Items[inventory->Get(i)].wdata->count;
				item->id = inventory->Get(i);
				ItemCountUpdate(item);
				writefItem(Item::Items[inventory->Get(i)].wdata, inventory->Get(i));
				return;
			}
		}
		int itemid = Item::CreateItem(item->id, item->count);
		WriteNewItem(itemid);
	}
	else {					// id-> ItemKey
		ItemCountUpdate(item); 
		return;
	}


}

void InventoryManager::SwapSlot(std::vector<int> NewInv)
{
	printf("-- inv update --\n");
	for (int i = 0; i < 30; i++) {
		inventory->Set(NewInv[i], i);
	}
}

void InventoryManager::ItemCountUpdate(fItemT * item)
{

	if (item->count < 1)
	{
		Item::Items.erase(item->id);
		Item::SetUserItem(item->id);
		inventory->Set(0, inventory->GetSlotNum(item->id));
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
