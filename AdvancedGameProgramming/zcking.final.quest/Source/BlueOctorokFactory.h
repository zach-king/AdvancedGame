#pragma once

#include "ObjectFactory.h"

class BlueOctorokFactory : public ObjectFactory
{
public:
	BlueOctorokFactory();
	~BlueOctorokFactory();
	std::unique_ptr<Object> create();
};