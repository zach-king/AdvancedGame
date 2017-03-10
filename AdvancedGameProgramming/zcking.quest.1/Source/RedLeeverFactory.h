#pragma once

#include "ObjectFactory.h"

// Red Leever Factory
class RedLeeverFactory : public ObjectFactory
{
public:
	RedLeeverFactory();
	~RedLeeverFactory();
	std::unique_ptr<Object> create();
};