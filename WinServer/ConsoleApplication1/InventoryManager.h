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

	void writefItem(int id, int slotNum);

	void WriteNewItem(int id);
	
	void InvUpdate(fItemT *);
	void SwapSlot(std::vector<int>);
	void UseItem(fItemT *);
	fItemT * Get(int);
};

