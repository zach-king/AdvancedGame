#pragma once

#include "OffScreenComponent.h"
#include "Game.h"

class TriggerNextLevelComponent : public OffScreenComponent
{
public:
	TriggerNextLevelComponent();
	TriggerNextLevelComponent(std::shared_ptr<Object> owner);
	~TriggerNextLevelComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);

protected:
	void Trigger(); // called when owner goes off screen
	Game* game; // used to load next level
};