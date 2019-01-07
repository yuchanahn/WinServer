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

	void WriteSome();

	void EquipSome(int objNum, int slotNum);

	EquipManager(int id);
	~EquipManager();
};

