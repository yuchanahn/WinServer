#include "Inventory.h"
#include "MysqlManager.h"


Inventory::Inventory(int id)
{
	MysqlManager m;
	m.GetPlayerInventory(id, inventory);
}

Inventory::~Inventory()
{

}

int Inventory::Get(int index)
{
	return inventory[index];
}
