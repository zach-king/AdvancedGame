#pragma once

#include "Definitions.h"
#include "Object.h"
#include "Component.h"
#include "PhysicsDevice.h"

#include <memory>

class ProjectileComponent : public Component
{
public:
	ProjectileComponent();
	ProjectileComponent(std::shared_ptr<Object> owner);
	~ProjectileComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	void Update();
	bool Finish();

protected:
	GAME_INT lifetime; // how many frames the projectile lives
	GAME_INT framesPassed; // basically a health counter based on frames
	PhysicsDevice* pDevice;
};