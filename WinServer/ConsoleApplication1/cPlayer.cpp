#include "COMPONENT_H.h"
#include "MysqlManager.h"
#include "FCDataManager.h"
#include "PlayerStateManager.h"
#include "PlayerPositionManager.h"

cPlayer::~cPlayer()
{
}

void cPlayer::Start()
{
	ReadManager::ReadSome[Class::Class_SendMeStat] = [this](PackData* data, std::shared_ptr<session> client) 
	{
		if (data->Get<SendMeStat>()->StatDataType == Class::Class_MonsterStat) {
			client->UseStrand([=]() {
				// ���� ��ȣ �ҷ�.
				// ���� ���� �� ����Ʈ.
				printf("���� ���� ��û, ���� ��ȣ : %d\n", data->Get<SendMeStat>()->ID);
			});
		}
		else {
			client->UseStrand([=]() {
				auto SMT = data->Get<SendMeStat>();

				printf("%d�� %d�� State�� ��û��.\n", client->id, session::InputSession[SMT->ID]->state->wdata->ID);
				auto t = session::InputSession[SMT->ID]->state->wdata;
				printf("%d State : %d/%d \n", t->ID, t->HP, t->HPLim);

				session::InputSession[SMT->ID]->state->Write(client);
				delete data;
			});
		}
	};


	ReadManager::ReadSome[Class::Class_Player] = [this](PackData* data, std::shared_ptr<session> client) 
	{
		client->UseStrand([=]() {
			data->Get<Player, PlayerT>(client->position->wdata);
			client->position->Write();
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
					auto Target = session::InputSession[data->Get<PlayerStat>()->ID]->state;

					data->Get<PlayerStat, PlayerStatT>(Target->wdata);


					Target->Write();
				}
				else {
					printf("���� Ŭ���̾�Ʈ���� ��û ����. player ID : %d ����.\n", data->Get<PlayerStat>()->ID);
				}
				delete data;
			}
		});
	};
}

void cPlayer::Update()
{
}

void cPlayer::FristSend(std::shared_ptr<session> client)
{
	MysqlManager m;

	PlayerPositionManager * position_ = new PlayerPositionManager;
	PlayerStateManager * state_ = new PlayerStateManager;

	position_->wdata->pos.reset(m.GetPlayerPos(client->id));
	position_->wdata->cType = Class::Class_Player;
	state_->wdata = m.GetPlayerStat(client->id);

	client->position = position_;
	client->state = state_;

	FCDataManager fcdManager;

	fcdManager.wdata->ID = client->id;
	fcdManager.wdata->Pos.reset(client->position->wdata->pos.get());
	fcdManager.wdata->cType = Class::Class_FirstCharacterData;

	fcdManager.wdata->HP = client->state->wdata->HP;
	fcdManager.wdata->HPLim = client->state->wdata->HPLim;

	fcdManager.Write(client);
}