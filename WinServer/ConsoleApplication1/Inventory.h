#pragma once
#include "Item.h"

const int Inventory_MAX = 30;


class Inventory
{
	int inventory[Inventory_MAX];
	int id;
public:
	Inventory(int id);
	~Inventory();

	int Get(int index);
	void Set(int, int);
};

