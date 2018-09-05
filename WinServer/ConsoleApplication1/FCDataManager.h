#pragma once
#include "WriteManager.h"


class FCDataManager :
	public WriteManager<FirstCharacterData, FirstCharacterDataT>
{
public:
	FCDataManager();
	~FCDataManager();
};

