#pragma once

#include "ObjectFactory.h"

class RedOctorokFactory : public ObjectFactory
{
public:
	RedOctorokFactory();
	~RedOctorokFactory();
	std::unique_ptr<Object> create();
};