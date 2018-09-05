#pragma once
#include "Component.h"

class cServerFPS :
	public Component
{
	float dt  = 0;
	int  fps  = 0;


public:
	int d = 33;
	cServerFPS(InputComponent* input) : Component(input) {};
	~cServerFPS();

	virtual void Update();
};

