#pragma once

#include "ObjectFactory.h"

// Red Octorok Factory
class RedOctorokFactory : public ObjectFactory
{
public:
	RedOctorokFactory();
	~RedOctorokFactory();
	std::unique_ptr<Object> create();
};