#pragma once
#include "Object.h"
#include <memory>

// Base class for ObjectFactories
class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	virtual std::unique_ptr<Object> create() = 0;
};
