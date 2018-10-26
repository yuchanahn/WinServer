#include "PlayerStateManager.h"
#include "MysqlManager.h"


PlayerStateManager::PlayerStateManager()
{
}


PlayerStateManager::~PlayerStateManager()
{
	MysqlManager::GetInstance()->SetPlayerStat(wdata);
}

void PlayerStateManager::isLevelUp()
{
	while (true)
	{
		int exp = wdata->EXP - ((wdata->LV * 30) + (wdata->LV*wdata->LV));

		if (exp > 0)
		{
			wdata->LV++;

			wdata->EXP = exp;

			wdata->HPLim = ((wdata->LV * 100) + (30 * (20 + wdata->LV)));
			wdata->HP = wdata->HPLim;
			wdata->MPLim = ((wdata->LV * 100) + (30 * (20 + wdata->LV)));
			wdata->MP = wdata->MPLim;
		}
		else {
			break;
		}
	}

}

void PlayerStateManager::Update(PlayerStatT newState)
{
	*wdata = newState;
}
