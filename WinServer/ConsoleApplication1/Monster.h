#pragma once
#include "CPoint.h"
#include <string>
#include <memory>
#include <map>
#include <list>
#include <queue>


class MonsterPositionManager;
class MonsterStateManager;
class MonsterRewardManager;
class DamageWriter;
class session;


class oMonster
{
	static int MonsterId; 
	static std::map<oMonster*,CPoint<double>> monsterPath;
	
	std::queue<CPoint<double>> mMoveLoad;
	double fRand(double fMin, double fMax);
	bool isInRange(std::shared_ptr<session>);

public:
	
	bool isDead = false;
	bool isAttack = false;


	float RegenTime = 5;
	float Regen_dt = 0;


	float dt = 0;
	float ATKdt = 0;

	float RandomTime = 3.0f;

	float Speed;
	double Range;
	int RandRange;
	double MaxRange;

	int ATKAttribute;
	int ATKDamage;
	float ATKTime = 3;


	
	CPoint<double> StartPos;
	CPoint<double> RandomPos;
	CPoint<double> CurrentPos;
	CPoint<double> TargetPos;

	MonsterPositionManager	* Position;
	MonsterStateManager		* State;
	MonsterRewardManager	* Reward;

	std::shared_ptr<session> target = nullptr;

	oMonster();
	~oMonster();


	std::shared_ptr<session> GetTargetOrNull();
	void SetTargetPos_Random();

	CPoint<double> GetShortestPath();

	void UpdatePosition();
	void Attack();
	void Update();
	void Set(std::string Name, int ID, double sX, double sY, int Hp, int Exp, float Speed, float MaxRange, float FollowRange, float RandRange, int ATKAttribute, int ATKDamage, float ATKTime);
};