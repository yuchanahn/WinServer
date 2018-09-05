#pragma once
#include "Item.h"

const int Inventory_MAX = 30;


class Inventory
{
	int inventory[Inventory_MAX];

	//mysql 에서 받아서 저장.
	//







public:
	Inventory();
	~Inventory();

	int Get(int index);
};

