#pragma once
#include "WriteManager.h"
class EquipManager
{
	int mID;
	int mslot[4] = {0};
	std::shared_ptr<session> mclient;
public:
	WriteManager<fItem, fItemT> w;
	void Set(int nSlot, int value);
	int Get(int index);

	void write();

	EquipManager(std::shared_ptr<session> client);
	~EquipManager();
};

