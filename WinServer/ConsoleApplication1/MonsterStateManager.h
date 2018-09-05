#pragma once
#include "WriteManager.h"

class MonsterStateManager :
	public WriteManager<MonsterStat, MonsterStatT>
{
public:
	MonsterStateManager();
	~MonsterStateManager();
};

