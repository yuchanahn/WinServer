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
#include <list>
#include <stack>


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
	RandomTime = fRand(1, 3);
}

oMonster::~oMonster()
{}

std::shared_ptr<session> oMonster::GetTargetOrNull()
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

/*수정필요*/
CPoint<double> oMonster::GetShortestPath()
{
	CPoint<double> PathPos = CurrentPos;
	double SX = 1, SY = 1;
	double mRange = MaxRange;

	int MinCost = 0;
	CPoint<double> MinCostXY(0, 0);
	CPoint<double> FCostXY(0, 0);
	CPoint<int> PrevPos(0, 0);

	float FollowSpeed = Speed;
	if (Speed < 0.7) {
		FollowSpeed = 0.7;
	}

	while (true) {

		int MinCost = 0;

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (!((i == 0) && (j == 0)))
				{
					auto x = (i * SX) * FollowSpeed;
					auto y = (j * SY) * FollowSpeed;

					double l = (TargetPos.x - (PathPos.x + x)), r = (TargetPos.y - (PathPos.y + y));
					if (l < 0) l = -l;
					if (r < 0) r = -r;

					bool bGetCost = true;
					for (auto mon : oMonster::monsterPath)
					{
						if (mon.first->target == target)
						{
							if (GetDistance(mon.second, CPoint<double>(PathPos.x + x, PathPos.y + y)) < mRange)
							{
								bGetCost = false;
								break;
							}
						}
					}

					if (!mMoveLoad.empty())
						if ((i == -PrevPos.x) && (j == -PrevPos.y))
							bGetCost = false;
						else
						{
							printf("x- %d, %d\ny- %d, %d\n", i, -PrevPos.x, j, -PrevPos.y);
						}


					if (bGetCost)
					{
						double H = (l + r);
						double G = 0;
						if (((i + j) == 1) || ((i + j) == -1))
						{
							G = 10;
						}
						else
						{
							G = 14;
						}

						int Cost = G + H * 10;

						if (Cost <= MinCost || MinCost == 0) {
							MinCost = Cost;

							MinCostXY.Set(PathPos.x + x, PathPos.y + y);
							PrevPos.Set(i, j);
						}
					}
				}
			}
		}
		if (GetDistance(TargetPos, MinCostXY) < mRange)
		{
			if (MinCost == 0)
			{
				return CPoint<double>(CurrentPos.x, CurrentPos.y);
			}
			if (mMoveLoad.empty())
				return MinCostXY;
			auto pos = mMoveLoad.front();
			mMoveLoad.pop();
			return pos;
		}
		else {
			if (MinCost == 0)
			{
				return CPoint<double>(CurrentPos.x, CurrentPos.y);
			}
			mMoveLoad.push(CPoint<double>(MinCostXY));
			PathPos = MinCostXY;


			if (mMoveLoad.size() > 20)
			{
				return CPoint<double>(CurrentPos.x, CurrentPos.y);
			}
		}
	}

}

void oMonster::UpdatePosition()
{
	target = GetTargetOrNull();

	if (target == nullptr)
	{
		TargetPos.Set(RandomPos);
	}
	else
	{
		TargetPos.Set(target->position->wdata->pos->x(), target->position->wdata->pos->z());
	}

	auto S = GetDistance(TargetPos, CurrentPos);
	if (!isAttack) {
		if ((MaxRange < S))
		{
			//if (target != nullptr)
			//{
			//	CPoint<double> Path;
			//	if (mMoveLoad.empty()) {
			//		Path = GetShortestPath();
			//	}
			//	else {
			//		Path = mMoveLoad.front();
			//		mMoveLoad.pop();
			//	}
			//	CurrentPos.x = Path.x;
			//	CurrentPos.y = Path.y;
			//}
			//else {
			CurrentPos.x += ((TargetPos.x - CurrentPos.x) / S)*Speed;
			CurrentPos.y += ((TargetPos.y - CurrentPos.y) / S)*Speed;
			//}
			//monsterPath[this] = CurrentPos;

			Position->wdata->Ani = 0.1f;
		}
		else
		{
			Position->wdata->Ani = 0.0f;

			if (target != nullptr) Attack();
		}
	}

	Position->wdata->pos.reset(new Vec3(CurrentPos.x, 0, CurrentPos.y));
	if (target != nullptr) {
		Position->wdata->TargetID = target->id;
		Position->wdata->TargetPos.reset(new Vec3(TargetPos.x, 0, TargetPos.y));
	}

}


void oMonster::Attack() {
	Position->wdata->Ani = 0.2f;
	Position->wdata->mDamage = ATKDamage;
	isAttack = true;
	Position->wdata->TargetID = target->id;
	ATKdt = 0;
}

void oMonster::Update()
{
	ATKdt += Time::deltaTime;

	dt += Time::deltaTime;
	if (dt > RandomTime)
	{
		dt = 0;
		SetTargetPos_Random();
		RandomTime = fRand(1, 3);
	}
	if (ATKdt > ATKTime)
	{
		isAttack = false;
	}	
	if ((ATKdt > ATKTime/2) && isAttack)
	{
		Position->wdata->Ani = 0.0f;
	}

	if (isDead)
	{
		Regen_dt += Time::deltaTime;
		monsterPath.erase(this);
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

void oMonster::Set(std::string Name,
	int ID, double sX, double sY, int Hp, int Exp,
	float Speed, float MaxRange, float FollowRange, float RandRange,
	int ATKAttribute, int ATKDamage, float ATKTime
)
{
	State->wdata->MonName = Name;
	State->wdata->HP = Hp;
	State->wdata->MAXHP = Hp;
	State->wdata->ID = ID;
	Position->wdata->ID = ID;
	Reward->wdata->exp = Exp;
	Reward->wdata->MonID = ID;
	this->MaxRange = MaxRange;
	this->Speed = Speed;
	this->RandRange = RandRange;
	this->Range = FollowRange;
	this->ATKAttribute = ATKAttribute;
	this->ATKDamage = ATKDamage;
	this->ATKTime = ATKTime;

	StartPos.Set(sX, sY);
}

int oMonster::MonsterId = 0;
std::map<oMonster*, CPoint<double>> oMonster::monsterPath;