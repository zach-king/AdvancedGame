#include "ProjectileComponent.h"
#include "BodyComponent.h"
#include "Game.h"
#include "Component.h"
#include "Definitions.h"
#include "GameFunctions.h"

#include <memory>


ProjectileComponent::ProjectileComponent() : Component()
{
}

ProjectileComponent::ProjectileComponent(std::shared_ptr<Object> owner) : Component(owner)
{
	framesPassed = 0;
}

ProjectileComponent::~ProjectileComponent()
{
}

bool ProjectileComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	lifetime = inits.arrow_life;

	return true;
}

std::unique_ptr<Object> ProjectileComponent::Update()
{
	framesPassed++;

	if (framesPassed > lifetime)
	{
		// Set to destroy
		_owner->setIsDead(true);
	}

	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	GAME_VEC pos = body->getPosition();
	GAME_FLT ang = body->getAngle();

	pos.x += ARROW_SPEED * cosf(degToRads(ang - 90)); // cos for x component
	pos.y += ARROW_SPEED * sinf(degToRads(ang - 90)); // sin for y component

	body->setPosition(pos);

	return nullptr;
}

bool ProjectileComponent::Finish()
{
	return true;
}