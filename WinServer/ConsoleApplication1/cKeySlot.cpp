#include "COMPONENT_H.h"
#include "MysqlManager.h"


void cKeySlot::StartKeySlot(int id)
{
	mkeySlots[id] = new int[EKeySlot::last];
	MysqlManager::GetInstance()->GetKeySlot(mkeySlots[id], id);

	std::vector<int> v(30);


	for (int i = 0; i < EKeySlot::last; i++) 
	{
		v[i] = mkeySlots[id][i];
	}

	WriteManager<fKeySlot, fKeySlotT> w;
	w.wdata->cType = Class::Class_fKeySlot;
	w.wdata->slotNum = v;
	w.Write(session::InputSession[id]->shared_from_this());
}

void cKeySlot::EndKeySlot(int id)
{
	if(mkeySlots.find(id) != mkeySlots.end()) {
		MysqlManager::GetInstance()->SetKeySlot(mkeySlots[id], id);
		delete mkeySlots[id];
		mkeySlots.erase(id);
	}
}


cKeySlot::~cKeySlot()
{
}


void cKeySlot::Start()
{
	ReadManager::ReadSome[Class::Class_fKeySlot] = [this](PackData* data, std::shared_ptr<session> client)
	{
		auto slot = data->Get<fKeySlot>();

		for (int i = 0; i < EKeySlot::last; i++) 
		{
			mkeySlots[client->id][i] = slot->slotNum[i];
		}
		delete data;
	};
}


std::map<int, int*> cKeySlot::mkeySlots;