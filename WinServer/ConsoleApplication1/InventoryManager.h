#pragma once
#include <vector>

class Inventory;

struct fItemT;

class InventoryManager
{
	Inventory * inventory;
public:
	InventoryManager(int ID);
	~InventoryManager();

	void Write(int id);
	
	void InvUpdate(fItemT *);
	void SwapSlot(std::vector<int>);
	void UseItem(fItemT *);
	fItemT * Get(int);
};

