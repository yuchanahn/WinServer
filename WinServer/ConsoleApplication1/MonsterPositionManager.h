#pragma once
#include "WriteManager.h"

class MonsterPositionManager :
	public WriteManager<Monster, MonsterT>
{
public:
	MonsterPositionManager();
	~MonsterPositionManager();
};

