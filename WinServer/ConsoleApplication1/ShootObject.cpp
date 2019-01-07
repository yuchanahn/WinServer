#include "ShootObject.h"
#include <iostream>


ShootObject::ShootObject(CPoint<float> cPos, CPoint<float> tPos, float Speed, float Range)
	: cPos_(cPos), tPos_(tPos), speed_(Speed), range_(Range)
{}


ShootObject::~ShootObject()
{
}

void ShootObject::Move()
{
	S = GetDistance(tPos_, cPos_);
	cPos_.x += ((tPos_.x - cPos_.x) / S) * speed_;
	cPos_.y += ((tPos_.y - cPos_.y) / S) * speed_;
	
	auto smpS = (S - GetDistance(tPos_, cPos_));
	if (smpS < 0)smpS *= -1;
	
	S2 += smpS;
	if(speed_ > 2)
		speed_ -= V;
}

bool ShootObject::IsInRange()
{
	if (S2 >= range_/* S <= .1f*/)
	{
		return true;
	}
	return false;
}
