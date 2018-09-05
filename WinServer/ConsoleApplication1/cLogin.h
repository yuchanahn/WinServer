#pragma once
#include "Component.h"
#include "WriteManager.h"


class cLogin :
	public Component,
	public WriteManager<Login, LoginT>
{
public:
	cLogin(InputComponent* input) : Component(input) {};
	~cLogin();

	virtual void Start();
	void isSuccess(std::shared_ptr<session> client);
	void isNonSuccess(std::shared_ptr<session> client);
};

