#pragma once
#include "Component.h"
#include <map>
#include <queue>
//#include "WriteManager.h"

class ShootObject;


class cEffect :
	public Component
{
	float sendRate = 0.1;
	float dt = 0;
	int NUM = 1;
	std::queue<int> ReNum;
	std::queue<int> Remove;
	std::map<int, WriteManager<fIG_EffectPos, fIG_EffectPosT>> ProjectileSkills;
	std::map<int, ShootObject*> ProjectileObj;
	std::map<fIG_EffectPosT * , fIG_ProjectileEffectT> ProjectileSkillsInfo;

public:
	cEffect(InputComponent* input) : Component(input) {};
	~cEffect();


	virtual void Start();
	void PosUpdate();
	void ProjectileSkillEnd(int eftID);
	virtual void Update();
};