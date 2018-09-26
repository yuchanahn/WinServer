#include "PlayerPositionManager.h"
#include "MysqlManager.h"

PlayerPositionManager::PlayerPositionManager()
{
}


PlayerPositionManager::~PlayerPositionManager()
{
	MysqlManager::GetInstance()->SetPlayerPos(wdata);
}

void PlayerPositionManager::Update(PlayerT* p)
{
	
}
