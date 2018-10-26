#pragma once
#include "CPoint.h"
#include <string>
#include <memory>


class MonsterPositionManager;
class MonsterStateManager;
class MonsterRewardManager;
class session;


class oMonster
{
	static int MonsterId; 
	
	double fRand(double fMin, double fMax);
	bool isInRange(std::shared_ptr<session>);


public:
	
	bool isDead = false;


	float RegenTime = 5;
	float Regen_dt = 0;


	float dt = 0;
	float RandomTime = 3.0f;

	float Speed;
	double Range;
	int RandRange;
	double MaxRange;
	
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


	std::shared_ptr<session> GetTarget();
	void SetTargetPos_Random();

	void UpdatePosition();
	void Update();
	void Set(std::string,int,double,double,int,int);
};