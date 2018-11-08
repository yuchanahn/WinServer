#include "EquipManager.h"
#include "MysqlManager.h"


void EquipManager::Set(int nSlot, int value)
{
	mslot[nSlot] = value;
}

int EquipManager::Get(int index)
{
	return mslot[index];
}

void EquipManager::write()
{
	w.wdata->cType = Class::Class_fEquip;
	w.Write(mclient);
}

EquipManager::EquipManager(std::shared_ptr<session> client)
	: mID(client->id) , mclient(client->shared_from_this())
{}


EquipManager::~EquipManager()
{
	MysqlManager::GetInstance()->SetEquip(mslot,mID);
}
