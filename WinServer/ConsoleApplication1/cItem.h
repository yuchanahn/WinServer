#pragma once
#include "Component.h"

class cItem :
	public Component
{
public:
	cItem(InputComponent* input) : Component(input) {};
	~cItem();

	void Start();
};

