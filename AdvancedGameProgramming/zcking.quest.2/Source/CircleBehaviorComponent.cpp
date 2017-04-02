#include "CircleBehaviorComponent.h"

CircleBehaviorComponent::CircleBehaviorComponent() : Component()
{
}

CircleBehaviorComponent::CircleBehaviorComponent(std::shared_ptr<Object> owner) : Component(owner)
{
}

CircleBehaviorComponent::~CircleBehaviorComponent()
{
}

bool CircleBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	return true;
}

std::unique_ptr<Object> CircleBehaviorComponent::Update()
{
	return nullptr;
}

bool CircleBehaviorComponent::Finish()
{
	return false;
}