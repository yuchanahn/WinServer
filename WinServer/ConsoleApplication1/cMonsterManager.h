#pragma once
#include "Component.h"
#include <map>
#include <string>

class oMonster;


class CreateMonsterData {
	std::string name;
	float X;
	float Y;
	int Hp;
	int Exp;
public:

	CreateMonsterData(std::string _name, float _x, float _y, int _hp, int _exp) :
		name(_name), X(_x), Y(_y), Hp(_hp), Exp(_exp)
	{}


	void Set(oMonster*,int);
};


class cMonsterManager :
	public Component
{
	float dt = .0f;
	float dt2 = .0f;
	float SendRate = .3f;
public:
	std::map<int, oMonster*> Monsters;

	cMonsterManager(InputComponent* input) : Component(input) {};
	~cMonsterManager();

	virtual void Start();
	virtual void Update();
};

