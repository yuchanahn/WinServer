#pragma once
#include "WriteManager.h"

class PlayerPositionManager :
	public WriteManager<Player,PlayerT>
{
public:
	PlayerPositionManager();
	~PlayerPositionManager();

	void Update(PlayerT*);
};

