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
	void SendDamage(int damage, bool bCri, Vec3 * pos_p, int dcolor = 1);
	virtual void Update();
	void FristSend(std::shared_ptr<session> client);


	InputComponent * MonsterManager;
};