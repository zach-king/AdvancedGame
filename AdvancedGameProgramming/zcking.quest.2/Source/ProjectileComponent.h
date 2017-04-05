#pragma once

#include "Component.h"
#include "Definitions.h"

#include <memory>

class Object;

class ProjectileComponent : public Component
{
public:
	ProjectileComponent();
	ProjectileComponent(std::shared_ptr<Object> owner);
	~ProjectileComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::unique_ptr<Object> Update();
	bool Finish();

protected:
	GAME_INT lifetime; // how many frames the projectile lives
	GAME_INT framesPassed;
};