#pragma once

#include "Component.h"
#include "Definitions.h"
#include "PhysicsDevice.h"

class Object;

class LinearMoveComponent : public Component
{
public:
	LinearMoveComponent();
	LinearMoveComponent(std::shared_ptr<Object> owner);
	~LinearMoveComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	void Update();
	bool Finish();

	GAME_FLT getSpeed();

	void setSpeed(GAME_FLT spd);

private:
	PhysicsDevice* pDevice;
	GAME_FLT speed;			// speed at which moves
};