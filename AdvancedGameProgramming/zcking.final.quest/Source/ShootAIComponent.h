#pragma once

#include "Component.h"
#include "Game.h"

class ShootAIComponent : public Component
{
public:
	ShootAIComponent();
	ShootAIComponent(std::shared_ptr<Object> owner);
	~ShootAIComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	void Update();
	bool Finish();

protected:
	GAME_FLT fireRate;
	void Shoot();
	GAME_FLT reloadFrames;
	bool canFire;
	Game* game;
};