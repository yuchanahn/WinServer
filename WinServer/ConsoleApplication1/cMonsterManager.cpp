#include "COMPONENT_H.h"
#include "Monster.h"
#include "MonsterStateManager.h"
#include "MonsterPositionManager.h"
#include "MysqlManager.h"

cMonsterManager::~cMonsterManager()
{
}

void cMonsterManager::Start()
{
	srand((unsigned int)time(NULL));
	MysqlManager m;
	auto monList = m.GetMonsterInfo();

	int n=0;

	for (auto i : monList)
	{
		for (int ii = 0; ii < 11; ii++) {
			auto mons = new oMonster();
			Monsters[++n] = mons;
			i->Set(mons, n);
			mons->SetTargetPos_Random();
			mons->CurrentPos.Set(mons->RandomPos);
			mons->CurrentPos.x += mons->StartPos.x;
			mons->CurrentPos.y += mons->StartPos.y;
		}
	}



	ReadManager::ReadSome[Class::Class_MonsterStat] = [this](PackData* data, std::shared_ptr<session> client)
	{
		auto MonsterState = data->Get<MonsterStat>();
		Monsters[MonsterState->ID]->State->wdata->HP = MonsterState->HP;
		Monsters[MonsterState->ID]->State->Write();
		delete data;
	};
}

void cMonsterManager::Update()
{
	
	dt += Time::deltaTime;


	if (dt > .1f)
	{
		dt = .0f;
		
		for (auto i : Monsters)
		{
			i.second->UpdatePosition();			
		}
	}
	
	for (auto i : Monsters)
	{
		i.second->Update();
	}
	
}



void CreateMonsterData::Set(oMonster * monster, int id)
{
	monster->Set(name,id,X,Y,Hp,Exp);
}