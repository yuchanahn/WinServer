#pragma once

class Inventory;

struct fItemT;

class InventoryManager
{
	Inventory * inventory;
public:
	InventoryManager(int ID);
	~InventoryManager();

	void Write(int id);

	fItemT * Get(int);
};

