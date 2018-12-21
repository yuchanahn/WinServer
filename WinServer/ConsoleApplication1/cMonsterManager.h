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
	float Speed;
	float Range;
	float FollowRange;
	float RandRange;
	int ATKAttribute;
	int ATKDamage;
	float ATKTime;

public:

	CreateMonsterData(std::string _name, float _x, float _y, int _hp, int _exp,
		float _speed, float _range, float _FollowRange, float _RandRange,
		int _ATKAttribute, int _ATKDamage, float _ATKTime

	) :
		name(_name), X(_x), Y(_y), Hp(_hp), Exp(_exp), Speed(_speed),
		Range(_range), FollowRange(_FollowRange), RandRange(_RandRange),
		ATKAttribute(_ATKAttribute), ATKDamage(_ATKDamage), ATKTime(_ATKTime)
	{}


	void Set(oMonster*, int);
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

	void SendDamage(int damage, bool bCri, Vec3* pos);

	virtual void Start();
	virtual void Update();
};

