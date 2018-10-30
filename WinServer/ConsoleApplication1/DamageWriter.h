#pragma once
#include "WriteManager.h"

class DamageWriter
{

	WriteManager<fDamage, fDamageT> damage;

public:
	DamageWriter(int damage, bool bCri);
	~DamageWriter();
};

