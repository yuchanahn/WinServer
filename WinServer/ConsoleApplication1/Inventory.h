#pragma once
#include "Item.h"

const int Inventory_MAX = 30;


class Inventory
{
	int inventory[Inventory_MAX];

public:
	Inventory(int id);
	~Inventory();

	int Get(int index);
};

