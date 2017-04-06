#include "Component.h"

#include <memory>

Component::Component()
{
	// Shoudln't allow for default constructor; component MUST have owner
	exit(1);
}

Component::Component(std::shared_ptr<Object> owner)
{
	_owner = owner;
}

Component::~Component()
{
	_owner = nullptr;
}

std::shared_ptr<Object> Component::GetOwner()
{
	return _owner;
}