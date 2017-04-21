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
	speed = inits.speed;

	// Get the body component for moving the projectile forward
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	GAME_FLT ang = body->getAngle();

	// Force vector
	GAME_VEC force = inits.force;

	// Magnify the force vector by arrow speed
	force.x *= speed;
	force.y *= speed;

	// Apply the linear force (but first position the arrow "in front" of spawner)
	// Make sure the angle is also pointing up
	body->setAngle(inits.angle);
	pDevice->SetLinearVelocity(_owner.get(), force);

	return true;
}

void ProjectileComponent::Update()
{
	// Increment framesPassed
	framesPassed++;

	// If lifetime has been lived (in frames), then set to die
	if (framesPassed > lifetime)
	{
		// Set to destroy
		_owner->setIsDead(true);
	}
}

bool ProjectileComponent::Finish()
{
	return true;
}