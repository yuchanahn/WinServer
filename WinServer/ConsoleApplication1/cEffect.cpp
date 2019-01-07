#include "COMPONENT_H.h"
#include "ReadManager.h"
#include "ShootObject.h"


cEffect::~cEffect()
{
}

void cEffect::Start()
{
	ReadManager::ReadSome[Class::Class_fIG_Effect] = [this](PackData* data, std::shared_ptr<session> client)
	{
		WriteManager<fIG_Effect, fIG_EffectT> w;
		w.wdata = data->Get<fIG_Effect>();

		w.Write();

		delete data;
	};

	ReadManager::ReadSome[Class::Class_fIG_EffectPos] = [this](PackData* data, std::shared_ptr<session> client)
	{
		ProjectileSkillEnd(data->Get<fIG_EffectPos>()->eftID);

		delete data;
	};

	ReadManager::ReadSome[Class::Class_fIG_ProjectileEffect] = [this](PackData* data, std::shared_ptr<session> client)
	{
		server::UseStrand([=]() {
			auto projt = data->Get<fIG_ProjectileEffect>();



			int id;
			if (ReNum.empty()) {
				id = NUM++;
			}
			else {
				id = ReNum.front();
				ReNum.pop();
			}

			auto NewSkill = ProjectileSkills[id];

			ProjectileObj[id]  = new ShootObject(
					CPoint<float>(projt->x, projt->z), 
					CPoint<float>(projt->tx, projt->tz), 
					projt->speed,
					projt->range);
			ProjectileObj[id]->V = projt->speed/10;

			
			ProjectileSkillsInfo[NewSkill.wdata] = *projt;


			NewSkill.wdata->cType = Class::Class_fIG_EffectPos;
			NewSkill.wdata->eftName = projt->eftName;

			NewSkill.wdata->x = projt->x;
			NewSkill.wdata->y = projt->y;
			NewSkill.wdata->z = projt->z;

			NewSkill.wdata->rx = projt->tx;
			NewSkill.wdata->ry = projt->ty;
			NewSkill.wdata->rz = projt->tz;
			NewSkill.wdata->rw = client->id;

			NewSkill.wdata->eftID = id;



			delete data; 
		});
	};
}


void cEffect::PosUpdate()
{
	for (auto i : ProjectileSkills) {
		i.second.wdata->x = ProjectileObj[i.first]->cPos_.x;
		i.second.wdata->z = ProjectileObj[i.first]->cPos_.y;
	}
}

void cEffect::ProjectileSkillEnd(int eftID)
{
	ProjectileSkills[eftID].wdata->eftID *= -1;
	ProjectileSkills[eftID].Write();
	Remove.push(eftID);
}


void cEffect::Update() 
{
	dt += Time::deltaTime;
	if (dt > sendRate) {
		dt = 0;

		while (!Remove.empty())
		{
			printf("Remove\n");
			auto i = Remove.front();
			ProjectileSkillsInfo.erase(ProjectileSkills[i].wdata);
			ProjectileSkills.erase(i);
			ProjectileObj.erase(i);
			Remove.pop();
		}

		for (auto i : ProjectileSkills) {
			 i.second.Write();
		}

		for (auto i : ProjectileObj) {
			i.second->Move();
			 if (i.second->IsInRange())
			 {
				 ProjectileSkillEnd(i.first);
			 }
		}

		while (!Remove.empty()) 
		{
			printf("Remove\n");
			auto i = Remove.front();
			ProjectileSkillsInfo.erase(ProjectileSkills[i].wdata);
			ProjectileSkills.erase(i);
			ProjectileObj.erase(i);
			Remove.pop();
		}

		PosUpdate();
	}
}