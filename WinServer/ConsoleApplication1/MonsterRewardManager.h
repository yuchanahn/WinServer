#pragma once
#include "WriteManager.h"
class MonsterRewardManager :
	public WriteManager<fReward, fRewardT>
{
public:
	MonsterRewardManager();
	~MonsterRewardManager();
};

