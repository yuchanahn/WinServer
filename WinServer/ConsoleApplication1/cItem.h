#pragma once
#include "Component.h"

class cItem :
	public Component
{
public:
	cItem(InputComponent* input) : Component(input) {};
	~cItem();

	void Start();

	void DropEND(int ItemID);

	void GetDropItem(std::shared_ptr<session> client);

};

