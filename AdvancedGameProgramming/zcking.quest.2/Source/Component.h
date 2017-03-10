#pragma once

#include <memory>
#include "Object.h"

class Component
{
public:
	Component(std::shared_ptr<Object> owner);
	~Component();
	void OwnerDestroyed();
	std::shared_ptr<Object> GetOwner();
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Finish() = 0;

protected:
	std::shared_ptr<Object> _owner;
};