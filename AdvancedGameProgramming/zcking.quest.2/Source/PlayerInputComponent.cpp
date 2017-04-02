#include "PlayerInputComponent.h"

PlayerInputComponent::PlayerInputComponent() : Component()
{
}

PlayerInputComponent::PlayerInputComponent(std::shared_ptr<Object> owner) : Component(owner)
{
}

PlayerInputComponent::~PlayerInputComponent()
{
}

bool PlayerInputComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	return true;
}

std::unique_ptr<Object> PlayerInputComponent::Update()
{
	return nullptr;
}

bool PlayerInputComponent::Finish()
{
	return false;
}