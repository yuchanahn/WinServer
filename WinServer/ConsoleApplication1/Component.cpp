#include "Component.h"
#include "InputComponent.h"



Component::Component()
{
	Parent_ = nullptr;
}

Component::Component(InputComponent* Parent) : Parent_(Parent)
{}

Component::~Component()
{}

