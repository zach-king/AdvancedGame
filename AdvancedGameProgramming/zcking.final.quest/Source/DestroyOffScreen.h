#pragma once

#include "OffScreenComponent.h"

class DestroyOffScreen : public OffScreenComponent
{
public:
	DestroyOffScreen();
	DestroyOffScreen(std::shared_ptr<Object> owner);
	~DestroyOffScreen();

protected:
	void Trigger();
};