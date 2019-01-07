#include "EquipManager.h"
#include "MysqlManager.h"
#include "Item.h"

void EquipManager::Set(int nSlot, int value)
{
	if (mslot[nSlot] != value) {

		if(value != 0)	EquipSome(Item::Items[value].wdata->id, nSlot);
		else			EquipSome(-Item::Items[mslot[nSlot]].wdata->id, nSlot);
		
		mslot[nSlot] = value;
	}
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
			EquipSome(Item::Items[mslot[i]].wdata->id,i);
		}
	}
}
void EquipManager::WriteSome()
{
	for (int i = 0; i < EQUIP_SLOT_MAX; i++)
	{
		if (mslot[i] != 0)
		{
			EquipSome(Item::Items[mslot[i]].wdata->id, i);
		}
	}
}



void EquipManager::EquipSome(int objNum, int slotNum) {
	WriteManager<fEquipSome, fEquipSomeT> w;
	w.wdata->cType = Class::Class_fEquipSome;
	w.wdata->objNum = objNum;
	w.wdata->pID = mID;
	w.wdata->slotNum = slotNum;
	printf("SEND SLOT NUM : %d(PID)\n", slotNum);
	printf("SEND OBJ  NUM : %d(PID)\n", objNum);
	w.Write();
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
