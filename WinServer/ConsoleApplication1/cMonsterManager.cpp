#include "COMPONENT_H.h"
#include "Monster.h"
#include "MonsterStateManager.h"
#include "MonsterPositionManager.h"
#include "MonsterRewardManager.h"
#include "MysqlManager.h"
#include "PlayerStateManager.h"

cMonsterManager::~cMonsterManager()
{
}

void cMonsterManager::Start()
{

	srand((unsigned int)time(NULL));

	auto monList = MysqlManager::GetInstance()->GetMonsterInfo();

	int n = 0;

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
		
		printf("monster State [HP : %d -> %d]\n", Monsters[MonsterState->ID]->State->wdata->HP, MonsterState->HP);
		
		Monsters[MonsterState->ID]->State->wdata->HP = MonsterState->HP;

		if (Monsters[MonsterState->ID]->State->wdata->HP < 1)
		{
			server::UseStrand([=]() {Monsters[MonsterState->ID]->isDead = true; });
			Monsters[MonsterState->ID]->State->wdata->HP = 0;
			client->state->wdata->EXP += Monsters[MonsterState->ID]->Reward->wdata->exp;
			client->state->isLevelUp();
		}

		Monsters[MonsterState->ID]->State->Write();
		client->state->Write();
		delete data;
	};
}

void cMonsterManager::Update()
{
	
	dt += Time::deltaTime;


	if (dt > .1f)
	{
		dt2 += dt;
		dt = .0f;

		for (auto i : Monsters)
		{
			i.second->UpdatePosition();			
		}
		if (dt2 > SendRate) {
			dt2 = 0;		
			for (auto i : Monsters)
			{
				i.second->Position->Write();
			}
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
