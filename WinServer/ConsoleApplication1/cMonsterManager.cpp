#include "COMPONENT_H.h"
#include "Monster.h"
#include "MonsterStateManager.h"
#include "MonsterPositionManager.h"
#include "MonsterRewardManager.h"
#include "MysqlManager.h"
#include "PlayerStateManager.h"
#include "PlayerPositionManager.h"

cMonsterManager::~cMonsterManager()
{
}

void cMonsterManager::SendDamage(int damage, bool bCri, Vec3* pos_p)
{
	WriteManager<fDamage, fDamageT> mdamage;
	mdamage.wdata->cType = Class::Class_fDamage;
	mdamage.wdata->bCri = bCri;
	mdamage.wdata->damage = damage;
	mdamage.wdata->Pos.reset(pos_p);
	mdamage.Write();
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
		auto mMonster = Monsters[MonsterState->ID];



		printf("monster State [HP : (%d%d)%d]\n", mMonster->State->wdata->HP, MonsterState->HP, mMonster->State->wdata->HP + MonsterState->HP);
		
		mMonster->State->wdata->HP += MonsterState->HP;
		
		if (mMonster->State->wdata->HP < 1)
		{
			server::UseStrand([=]() {mMonster->isDead = true; });
			mMonster->State->wdata->HP = 0;
			client->state->wdata->EXP += mMonster->Reward->wdata->exp;
			client->state->isLevelUp();
		}

		Monsters[MonsterState->ID]->State->Write();
		client->state->Write();

		auto monPos = mMonster->Position->wdata;

		SendDamage(MonsterState->HP, false, new Vec3(monPos->pos->x() , monPos->pos->y()+1, monPos->pos->z()));
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
			if(!i.second->isDead)
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
