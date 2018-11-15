#pragma once
#include "Component.h"

class cEquip :
	public Component
{
public:
	cEquip(InputComponent* input) : Component(input) {};
	~cEquip();
	virtual void Start();
};