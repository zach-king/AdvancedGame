#include "ProjectileComponent.h"
#include "BodyComponent.h"
#include "Game.h"
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
	framesPassed = 0;

	return true;
}

std::unique_ptr<Object> ProjectileComponent::Update()
{
	// Increment framesPassed
	framesPassed++;

	// If lifetime has been lived (in frames), then set to die
	if (framesPassed > lifetime)
	{
		// Set to destroy
		_owner->setIsDead(true);
	}

	// Get the body component for moving the projectile forward
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	GAME_VEC pos = body->getPosition();
	GAME_FLT ang = body->getAngle();

	// Modify position (linear movement)
	pos.x += ARROW_SPEED * cosf(degToRads(ang - 90)); // cos for x component
	pos.y += ARROW_SPEED * sinf(degToRads(ang - 90)); // sin for y component

	// Apply new position
	body->setPosition(pos);

	return nullptr;
}

bool ProjectileComponent::Finish()
{
	return true;
}