#pragma once

class Inventory;
struct fItemT;

class InventoryManager
{
	Inventory * inventory;
public:
	InventoryManager(int ID);
	~InventoryManager();

	fItemT * Get(int);
};

