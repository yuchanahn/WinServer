#include "Inventory.h"
#include "MysqlManager.h"


Inventory::Inventory(int id)
{
	MysqlManager m;
	m.GetPlayerInventory(id, inventory);
	this->id = id;
}

Inventory::~Inventory()
{
	MysqlManager m;
	m.SetInv(inventory,id);
}

int Inventory::Get(int index)
{
	return inventory[index];
}

void Inventory::Set(int val, int index)
{
	inventory[index] = val;
}
