#include "COMPONENT_H.h"
#include "MysqlManager.h"
#include "FCDataManager.h"
#include "PlayerStateManager.h"
#include "PlayerPositionManager.h"
#include "Monster.h"
#include "MonsterStateManager.h"
#include "EquipManager.h"

cPlayer::~cPlayer()
{
}

void cPlayer::Start()
{
	ReadManager::ReadSome[Class::Class_SendMeStat] = [this](PackData* data, std::shared_ptr<session> client) 
	{
		if (data->Get<SendMeStat>()->StatDataType == Class::Class_MonsterStat) {
			client->UseStrand([=]() {
				MonsterManager->GetComponent<cMonsterManager>()->Monsters[data->Get<SendMeStat>()->ID]->State->Write(client);
				printf("%d>>GetMonsterState(%d)\n", client->id,data->Get<SendMeStat>()->ID);
			});
		}
		else {
			client->UseStrand([=]() {
				auto SMT = data->Get<SendMeStat>();

				printf("%d>>GetState(%d)\n", client->id, session::InputSession[SMT->ID]->state->wdata->ID);
				auto t = session::InputSession[SMT->ID]->state->wdata;
				printf("State(%d)   %d/%d \n", t->ID, t->HP, t->HPLim);

				session::InputSession[SMT->ID]->state->Write(client);
				session::InputSession[SMT->ID]->equipManager->WriteSome();
				delete data;
			});
		}
	};


	ReadManager::ReadSome[Class::Class_Player] = [this](PackData* data, std::shared_ptr<session> client) 
	{
		client->UseStrand([=]() {
			if (client->position != nullptr) {
				data->Get<Player, PlayerT>(client->position->wdata);
				client->position->Write();
			}
			delete data;
		});
	};

	ReadManager::ReadSome[Class::Class_PlayerStat] = [this](PackData* data, std::shared_ptr<session> client)
	{
		client->UseStrand([=]() {
			if (client->position == nullptr) 
			{
				FristSend(client->shared_from_this());
			}
			else
			{
				if (session::InputSession.find(data->Get<PlayerStat>()->ID) != session::InputSession.end()) {

					auto TargetClient = session::InputSession[data->Get<PlayerStat>()->ID];
					TargetClient->UseStrand([=]() {

						auto Target = TargetClient->state;

						if (Target != client->state)
						{
							Target->wdata->HP += data->Get<PlayerStat>()->HP;
						}
						else
						{
							Target->wdata->HP += data->Get<PlayerStat>()->HP;
							Target->wdata->MP += data->Get<PlayerStat>()->MP;
						}

						Target->Write();

						auto x = TargetClient->position->wdata->pos->x();
						auto y = TargetClient->position->wdata->pos->y();
						auto z = TargetClient->position->wdata->pos->z();

						SendDamage(data->Get<PlayerStat>()->HP, false, new Vec3(x, y, z)); 
						delete data;
					});
				}
				else {
					printf("좀비 클라이언트에게 요청 들어옴. player ID : %d 삭제.\n", data->Get<PlayerStat>()->ID);
				}
				
			}
		});
	};
}

void cPlayer::SendDamage(int damage, bool bCri, Vec3* pos_p, int dcolor)
{
	WriteManager<fDamage, fDamageT> mdamage;
	mdamage.wdata->cType = Class::Class_fDamage;
	mdamage.wdata->bCri = bCri;
	mdamage.wdata->damage = damage;
	mdamage.wdata->Pos.reset(pos_p);
	mdamage.wdata->dcolor = dcolor;
	mdamage.Write();
}


void cPlayer::Update()
{
}

void cPlayer::FristSend(std::shared_ptr<session> client)
{
	PlayerPositionManager * position_ = new PlayerPositionManager;
	PlayerStateManager * state_ = new PlayerStateManager;

	position_->wdata->pos.reset(MysqlManager::GetInstance()->GetPlayerPos(client->id));
	position_->wdata->cType = Class::Class_Player;
	std::string player_name;
	state_->wdata = MysqlManager::GetInstance()->GetPlayerStat(client->id, player_name);

	client->position = position_;
	client->state = state_;

	FCDataManager fcdManager;
	

	fcdManager.wdata->ID = client->id;
	fcdManager.wdata->Pos.reset(client->position->wdata->pos.get());
	fcdManager.wdata->cType = Class::Class_FirstCharacterData;

	fcdManager.wdata->HP = client->state->wdata->HP;
	fcdManager.wdata->HPLim = client->state->wdata->HPLim;

	fcdManager.wdata->MP = client->state->wdata->MP;
	fcdManager.wdata->MPLim = client->state->wdata->MPLim;
	fcdManager.wdata->EXP = client->state->wdata->EXP;
	fcdManager.wdata->Attack = client->state->wdata->Attack;
	fcdManager.wdata->LV = client->state->wdata->LV;
	fcdManager.wdata->Name = player_name.c_str();

	fcdManager.Write(client->shared_from_this());
}
