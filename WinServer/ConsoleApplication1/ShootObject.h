#pragma once
#include "CPoint.h"

class ShootObject
{
	float speed_;
	float range_;
	
	float S;
public:
	float V = 0.1f;
	float S2 = .0f;
	CPoint<float> cPos_;
	CPoint<float> tPos_;

	ShootObject(CPoint<float> cPos, CPoint<float> tPos, float Speed, float Range);
	~ShootObject();

	void Move();
	bool IsInRange();
};

