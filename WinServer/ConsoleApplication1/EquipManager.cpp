#include "EquipManager.h"
#include "MysqlManager.h"
#include "Item.h"

void EquipManager::Set(int nSlot, int value)
{
	mslot[nSlot] = value;
}

int EquipManager::Get(int index)
{
	return mslot[index];
}

void EquipManager::write(std::shared_ptr<session> client)
{
	for (int i = 0; i < EQUIP_SLOT_MAX; i++) 
	{
		if (mslot[i] != 0) 
		{
			*w.wdata = *Item::Items[mslot[i]].wdata;
			w.wdata->id = mslot[i];
			w.wdata->val8 = i;
			w.wdata->cType = Class::Class_fEquip;
			w.Write(client);
		}
	}
}

EquipManager::EquipManager(int id)
	: mID(id)
{
	MysqlManager::GetInstance()->GetEquipSlot(mslot,mID);
}


EquipManager::~EquipManager()
{
	MysqlManager::GetInstance()->SetEquip(mslot,mID);
}
