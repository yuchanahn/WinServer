#pragma once
#include "Component.h"
#include <map>


class cPlayer :
	public Component
{

	SendStateTo * SMTManager;

public:
	cPlayer(InputComponent* input) : Component(input) {};
	~cPlayer();

	virtual void Start();
	virtual void Update();
	void FristSend(std::shared_ptr<session> client);
};

