#pragma once
#include "Component.h"

class cChat :
	public Component
{
public:
	cChat(InputComponent* input) : Component(input) {};
	~cChat();
	virtual void Start();
};

