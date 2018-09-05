#pragma once
#include "InputComponent.h"

class Component
{
public:
	InputComponent * Parent_ = nullptr;

	virtual void Start()	{};
	virtual void Update()	{};




	template <typename T>
	T* AddComponent() {
		return ((InputComponent*)Parent_)->AddComponent<T>();
	}
	template <typename T>
	T* GetComponent() {
		return ((InputComponent*)Parent_)->GetComponent<T>();
	}


	Component();
	Component(InputComponent*);
	virtual ~Component();
};

