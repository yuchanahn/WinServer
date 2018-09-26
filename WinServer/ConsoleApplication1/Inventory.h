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
	int GetSlotNum(int Itemkey);
	void Set(int val, int index);
};

