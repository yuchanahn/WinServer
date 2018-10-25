#pragma once
#include <vector>

class Inventory;

struct fItemT;

class InventoryManager
{
	Inventory * inventory;
	int playerID;
public:
	InventoryManager(int ID);
	~InventoryManager();

	void Write();

	void writefItem(fItemT *, int id);

	void WriteNewItem(int id);
	
	void InvUpdate(fItemT *);
	void SwapSlot(std::vector<int>);
	void ItemCountUpdate(fItemT * item, int id);

	fItemT * Get(int);
};

