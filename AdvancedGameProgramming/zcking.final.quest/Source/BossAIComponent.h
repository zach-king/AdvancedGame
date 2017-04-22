#pragma once

#include "Component.h"
#include "Game.h"

class BossAIComponent : public Component
{
public:
	BossAIComponent();
	BossAIComponent(std::shared_ptr<Object> owner);
	~BossAIComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	void Update();
	bool Finish();

private:
	void Shoot(GAME_VEC posMod);
	bool canFire;
	GAME_FLT reloadFrames;
	Game* game;
};