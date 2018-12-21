#pragma once
#include "Component.h"

enum EKeySlot : int
{
	q = 0,
	w,
	e,
	r,
	a,
	s,
	d,
	f,
	last
};

class cKeySlot:
	public Component
{

	static std::map<int, int*> mkeySlots;

public:
	
	static void StartKeySlot(int id);
	static void EndKeySlot(int id);



	cKeySlot(InputComponent* input) : Component(input) {};
	~cKeySlot();
	virtual void Start();
};

