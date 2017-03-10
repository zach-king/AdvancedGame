#include "GameObject.h"
#include "Component.h"

Component::Component(std::shared_ptr<GameObject> owner) : _owner(owner){}

Component::~Component(){}

void Component::OwnerDestroyed()
{
	Finish();
	_owner = NULL;
}

std::shared_ptr<GameObject> Component::GetOwner()
{
	return(_owner);
}