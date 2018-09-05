#pragma once
#include <map>
#include <list>

class Component;

class InputComponent
{
	static int m_kOffset;

	std::map<int,Component*> Components;
	std::list<InputComponent*> InputComponents;
public:
	void AddComponent(InputComponent*);

	void Start();
	void Update();

	template <typename T>
	T* AddComponent() {
		Components[offset<T>()] = new T(this);
		return (T*)Components[offset<T>()];
	}
	template <typename T>
	T* GetComponent() {
		return (T*)Components[offset<T>()];
	}

	template <typename T>
	int offset() {
		static int s_offset = -1;
		if (s_offset == -1)
			s_offset = m_kOffset++;
		return s_offset;
	}
	

	InputComponent();
	~InputComponent();
};

