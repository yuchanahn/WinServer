#include "InventoryManager.h"
#include "Inventory.h"
#include "Item.h"

InventoryManager::InventoryManager(int id)
{
	inventory = new Inventory(id);
}


InventoryManager::~InventoryManager()
{
}

fItemT * InventoryManager::Get(int index)
{
	return Item::Items[inventory->Get(index)].wdata;
}
