#pragma once
#include <cmath>

template<typename T>
class CPoint
{
public:
	T x;
	T y;

	CPoint() : x(0), y(0) { }
	CPoint(T _x, T _y) : x(_x), y(_y) { }

	void Set(T _x,T _y) {
		x = _x;
		y = _y;
	}
	void Set(CPoint& obj) {
		x = obj.x;
		y = obj.y;
	}
};

template<typename T1, typename T2>
double GetDistance(const T1& p1, const T2& p2)
{
	return std::sqrt(double((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y)));
}