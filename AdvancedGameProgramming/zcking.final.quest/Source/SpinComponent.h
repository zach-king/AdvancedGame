#pragma once

#include "PhysicsDevice.h"
#include "Component.h"
#include "Definitions.h"

class Object;

class SpinComponent : public Component
{
public:
	SpinComponent();
	SpinComponent(std::shared_ptr<Object> owner);
	~SpinComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	void Update();
	bool Finish();

private:
	GAME_FLT speed;
	PhysicsDevice* pDevice;
};