#pragma once
#include "Object.h"
#include <memory>

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	virtual std::unique_ptr<Object> create() = 0;

protected:
	//static std::unique_ptr<ObjectFactory> instance; // singleton class design (used in constructors of children)
};
