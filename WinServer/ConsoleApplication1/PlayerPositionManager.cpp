#include "PlayerPositionManager.h"
#include "MysqlManager.h"

PlayerPositionManager::PlayerPositionManager()
{
}


PlayerPositionManager::~PlayerPositionManager()
{
	MysqlManager m;
	m.SetPlayerPos(wdata);
}

void PlayerPositionManager::Update(PlayerT* p)
{
	
}
