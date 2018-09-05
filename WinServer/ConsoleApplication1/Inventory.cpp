#include "Inventory.h"



Inventory::Inventory()
{

}


Inventory::~Inventory()
{

}

int Inventory::Get(int index)
{
	return inventory[index];
}
