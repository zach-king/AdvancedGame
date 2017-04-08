#pragma once

#include "Definitions.h"

#include <memory>

class Object;

class Component
{
public:
	// Constructors/Destructor
	Component();
	Component(std::shared_ptr<Object> owner);
	~Component();

	// Getter for _owner
	std::shared_ptr<Object> GetOwner();
	
	// Purely virtual functions to be overridden
	virtual bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers) = 0;
	virtual std::unique_ptr<Object> Update() = 0;
	virtual bool Finish() = 0;

protected:
	std::shared_ptr<Object> _owner; // the object which this component is attached to
};