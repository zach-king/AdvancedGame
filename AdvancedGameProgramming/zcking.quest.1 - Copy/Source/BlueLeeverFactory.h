#pragma once

#include "ObjectFactory.h"

class BlueLeeverFactory : public ObjectFactory
{
public:
	BlueLeeverFactory();
	~BlueLeeverFactory();
	std::unique_ptr<Object> create();
};