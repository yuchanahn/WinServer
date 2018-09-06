#pragma once
#include "Component.h"


class cInventory :
	public Component
{
public:
	cInventory(InputComponent* input) : Component(input) {};
	~cInventory();

	virtual void Start();
};

