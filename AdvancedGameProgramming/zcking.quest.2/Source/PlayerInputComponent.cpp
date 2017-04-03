#include "PlayerInputComponent.h"
#include "BodyComponent.h"
#include "Component.h"
#include "InputDevice.h"
#include "Definitions.h"

#include <memory>

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
	iDevice = initializers.iDevice;

	return true;
}

std::unique_ptr<Object> PlayerInputComponent::Update()
{
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	GAME_VEC pos = body->getPosition();
	if (iDevice->GetEvent(GAME_LEFT))
		pos.x -= LINK_SPEED;

	if (iDevice->GetEvent(GAME_RIGHT))
		pos.x += LINK_SPEED;

	if (iDevice->GetEvent(GAME_UP))
		pos.y -= LINK_SPEED;

	if (iDevice->GetEvent(GAME_DOWN))
		pos.y += LINK_SPEED;

	return nullptr;
}

bool PlayerInputComponent::Finish()
{
	return true;
}