#include "TriggerNextLevelComponet.h"

TriggerNextLevelComponent::TriggerNextLevelComponent() : OffScreenComponent()
{
}

TriggerNextLevelComponent::TriggerNextLevelComponent(std::shared_ptr<Object> owner)
	: OffScreenComponent(owner)
{
}

TriggerNextLevelComponent::~TriggerNextLevelComponent()
{
}

bool TriggerNextLevelComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	OffScreenComponent::Initialize(inits); // call parent first
	game = inits.game;
	return true;
}

void TriggerNextLevelComponent::Trigger()
{
	game->setProgress(true);
	_owner->setIsDead(true);
}