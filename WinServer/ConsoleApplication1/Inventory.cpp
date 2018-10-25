#include "Inventory.h"
#include "MysqlManager.h"


Inventory::Inventory(int id)
{
	MysqlManager::GetInstance()->GetPlayerInventory(id, inventory);
	this->id = id;
}

Inventory::~Inventory()
{
	MysqlManager::GetInstance()->SetInv(inventory,id);
}

int Inventory::Get(int index)
{
	return inventory[index];
}

int Inventory::GetSlotNum(int Itemkey)
{
	for (int i = 0; i < 30; i++) {
		if(inventory[i] == Itemkey)
			return i;
	}
	return -1;
}

void Inventory::Set(int val, int index)
{
	printf(" %2d |%d|\n", index, val);
	inventory[index] = val;
}
 