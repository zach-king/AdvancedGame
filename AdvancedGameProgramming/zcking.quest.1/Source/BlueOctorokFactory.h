#pragma once

#include "ObjectFactory.h"

// Blue Octorok Factory
class BlueOctorokFactory : public ObjectFactory
{
public:
	BlueOctorokFactory();
	~BlueOctorokFactory();
	std::unique_ptr<Object> create();
};