#include "PlayerStateManager.h"
#include "MysqlManager.h"


PlayerStateManager::PlayerStateManager()
{
}


PlayerStateManager::~PlayerStateManager()
{
	MysqlManager::GetInstance()->SetPlayerStat(wdata);
}

void PlayerStateManager::Update(PlayerStatT newState)
{
	*wdata = newState;
}
