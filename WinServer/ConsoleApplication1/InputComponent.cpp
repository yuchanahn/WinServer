#include "InputComponent.h"
#include "Component.h"


void InputComponent::AddComponent(InputComponent* component)
{
	InputComponents.push_back(component);
}

void InputComponent::Start()
{
	for (auto component : InputComponents)
		component->Start();
	for (auto component : Components)
		component.second->Start();
}

void InputComponent::Update()
{
	for (auto component : InputComponents)
		component->Update();
	for (auto component : Components)
		component.second->Update();
}

InputComponent::InputComponent()
{
	
}

InputComponent::~InputComponent()
{

}
int InputComponent::m_kOffset = 0;