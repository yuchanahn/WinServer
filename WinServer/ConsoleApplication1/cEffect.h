#pragma once
#include "Component.h"

class cEffect :
	public Component
{
public:
	cEffect(InputComponent* input) : Component(input) {};
	~cEffect();

	virtual void Start();
};