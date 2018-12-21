#pragma once
#include "Component.h"

class cSkillSlot :
	public Component
{
	const int SKILL_SLOT_MAX = 30;

	std::map<int, int*> mskillSlot;
public:
	cSkillSlot(InputComponent* input) : Component(input) {};
	void StartSkillSlot(int id);
	void EndSkillSlot(int id);
	~cSkillSlot();
	virtual void Start();
};

