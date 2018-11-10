#include "Monster.h"
#include "Base_generated.h"
#include "ClientSession.h"

#include "PlayerPositionManager.h"

#include "MonsterPositionManager.h"
#include "MonsterStateManager.h"
#include "MonsterRewardManager.h"
#include "Time.h"

#include <stdlib.h>
#include <float.h>
#include <time.h>


double oMonster::fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}
bool oMonster::isInRange(std::shared_ptr<session> target)
{
	

	if (target->position == nullptr)
		return false;
	if (target->isOffLine) {
		this->target = nullptr;
		return false;
	}

	CPoint<double> TargetPlayerPos(target->position->wdata->pos->x(), target->position->wdata->pos->z());

	auto S = GetDistance(TargetPlayerPos, CurrentPos);

	if (Range >= S) {
		return true;
	}
	else {
		return false;
	}
}

oMonster::oMonster()
{
	Position = new MonsterPositionManager;
	State = new MonsterStateManager;
	Reward = new MonsterRewardManager;

	Position->wdata->cType = Class::Class_Monster;
	State->wdata->cType = Class::Class_MonsterStat;
	Reward->wdata->cType = Class::Class_fReward;


	Range = 5;
	RandRange = 20;
	MaxRange = 1.5f;
	Speed = 0.3f;
	target = nullptr;

	State->wdata->HP = 100;
}

oMonster::~oMonster()
{}

std::shared_ptr<session> oMonster::GetTarget()
{
	if (target != nullptr) {
		if (isInRange(target->shared_from_this()))
		{
			return target->shared_from_this();
		}
	}
	for (auto Player_ : session::InputSession) {
		if (isInRange(Player_.second->shared_from_this()))
		{
			return Player_.second->shared_from_this();
		}
	}
	return nullptr;
}

void oMonster::SetTargetPos_Random()
{
	RandomPos.Set(fRand(-RandRange, RandRange), fRand(-RandRange, RandRange));
}

void oMonster::UpdatePosition()
{
	target = GetTarget();

	if (target == nullptr)
	{
		TargetPos.Set(RandomPos);
	}
	else 
	{
		TargetPos.Set(target->position->wdata->pos->x(), target->position->wdata->pos->z());
	}

	auto S = GetDistance(TargetPos, CurrentPos);

	if (MaxRange < S)
	{
		CurrentPos.x += ((TargetPos.x - CurrentPos.x) / S)*Speed;
		CurrentPos.y += ((TargetPos.y - CurrentPos.y) / S)*Speed;
		Position->wdata->Ani = 0.1f;
	}
	else
	{
		Position->wdata->Ani = 0.0f;
	}

	Position->wdata->pos.reset(new Vec3(CurrentPos.x, 0, CurrentPos.y));
	if (target != nullptr) {
		Position->wdata->TargetID = target->id;
		Position->wdata->TargetPos.reset(new Vec3(TargetPos.x,0,TargetPos.y));
	}
}

void oMonster::Update()
{
	dt += Time::deltaTime;
	if (dt > RandomTime) 
	{
		dt = 0;
		SetTargetPos_Random();
	}

	if (isDead)
	{
		Regen_dt += Time::deltaTime;

		if (Regen_dt > RegenTime) 
		{
			Regen_dt = 0;
			isDead = false;
			target = nullptr;
			SetTargetPos_Random();
			CurrentPos.x = RandomPos.x;
			CurrentPos.y = RandomPos.y;
			State->wdata->HP = State->wdata->MAXHP; 
			Position->Write();
			State->Write();
		}
	}
}

void oMonster::Set(std::string Name, int ID ,double sX, double sY, int Hp, int Exp)
{
	State->wdata->HP = Hp;
	State->wdata->MAXHP = Hp;
	State->wdata->ID = ID;
	Position->wdata->ID = ID;
	Reward->wdata->exp = Exp;
	Reward->wdata->MonID = ID;

	StartPos.Set(sX, sY);
}

int oMonster::MonsterId = 0;