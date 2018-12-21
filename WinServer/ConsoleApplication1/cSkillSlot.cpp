#include "COMPONENT_H.h"
#include "MysqlManager.h"

void cSkillSlot::StartSkillSlot(int id)
{
	mskillSlot[id] = new int[SKILL_SLOT_MAX];
	MysqlManager::GetInstance()->GetSkillSlot(mskillSlot[id], id);

	std::vector<int> v(30);

	for (int i = 0; i < SKILL_SLOT_MAX; i++)
	{
		v[i] = mskillSlot[id][i];
	}

	WriteManager<fSkillSlot, fSkillSlotT> w;
	w.wdata->cType = Class::Class_fSkillSlot;
	w.wdata->slotNum = v;
	w.Write(session::InputSession[id]->shared_from_this());
}

void cSkillSlot::EndSkillSlot(int id)
{
	if (mskillSlot.find(id) != mskillSlot.end()) {
		MysqlManager::GetInstance()->SetSkillSlot(mskillSlot[id], id);
		delete mskillSlot[id];
		mskillSlot.erase(id);
	}
}



cSkillSlot::~cSkillSlot()
{
}

void cSkillSlot::Start()
{
	ReadManager::ReadSome[Class::Class_fSkillSlot] = [this](PackData* data, std::shared_ptr<session> client)
	{
		auto slot = data->Get<fSkillSlot>();

		for (int i = 0; i < SKILL_SLOT_MAX; i++)
		{
			mskillSlot[client->id][i] = slot->slotNum[i];
		}

		delete data;
	};
}
