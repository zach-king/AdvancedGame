#pragma once

#include "ObjectFactory.h"

// Blue Leever Factory
class BlueLeeverFactory : public ObjectFactory
{
public:
	BlueLeeverFactory();
	~BlueLeeverFactory();
	std::unique_ptr<Object> create();
};