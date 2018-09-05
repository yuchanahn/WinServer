#pragma once
#include "Component.h"
#include "WriteManager.h"

class cPing :
	public Component,
	public WriteManager<ping,pingT>
{
public:
	cPing(InputComponent* input) : Component(input) {};
	~cPing();


	virtual void Start();
};
