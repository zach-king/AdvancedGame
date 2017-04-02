#include "SlideBehaviorComponent.h"

SlideBehaviorComponent::SlideBehaviorComponent() : Component()
{
}

SlideBehaviorComponent::SlideBehaviorComponent(std::shared_ptr<Object> owner) : Component(owner)
{
}

SlideBehaviorComponent::~SlideBehaviorComponent()
{
}

bool SlideBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	return true;
}

std::unique_ptr<Object> SlideBehaviorComponent::Update()
{
	return nullptr;
}

bool SlideBehaviorComponent::Finish()
{
	return false;
}