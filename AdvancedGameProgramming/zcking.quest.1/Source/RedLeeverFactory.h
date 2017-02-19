#pragma once

#include "ObjectFactory.h"

class RedLeeverFactory : public ObjectFactory
{
public:
	RedLeeverFactory();
	~RedLeeverFactory();
	std::unique_ptr<Object> create();
};