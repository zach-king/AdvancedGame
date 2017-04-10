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
	pDevice = inits.game->getPhysicsDevice();
	framesPassed = 0;

	// Get the body component for moving the projectile forward
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	GAME_VEC pos = body->getPosition();
	GAME_FLT ang = body->getAngle();

	// Force vector
	GAME_VEC force;
	if (ang == 0)
	{
		pos.y -= 32;
		force = VEC_DOWN;
	}
	else if (ang == 90)
	{
		pos.x += 32;
		force = VEC_RIGHT;
	}
	else if (ang == 180)
	{
		pos.y += 32;
		force = VEC_UP;
	}
	else
	{
		pos.x -= 32;
		force = VEC_LEFT;
	}

	// Magnify the force vector by arrow speed
	force.x *= ARROW_SPEED;
	force.y *= ARROW_SPEED;

	// Apply the linear force (but first position the arrow "in front" of spawner)
	body->setPosition(pos);
	pDevice->SetLinearVelocity(_owner.get(), force);

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

	return nullptr;
}

bool ProjectileComponent::Finish()
{
	return true;
}