#pragma once
#include "WriteManager.h"

class PlayerStateManager :
	public WriteManager<PlayerStat, PlayerStatT>
{
public:
	PlayerStateManager();
	~PlayerStateManager();

	void isLevelUp();
	void Update(PlayerStatT);
};

