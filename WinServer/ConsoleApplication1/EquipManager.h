#pragma once
#include "WriteManager.h"

class EquipManager
{
	int mID;
	int mslot[4] = {0};

public:
	WriteManager<fItem, fItemT> w;
	void Set(int nSlot, int value);
	int Get(int index);

	void write(std::shared_ptr<session> client);

	EquipManager(int id);
	~EquipManager();
};

