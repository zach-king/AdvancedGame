#include "CircleBehaviorComponent.h"
#include "BodyComponent.h"
#include "GameFunctions.h"
#include "Game.h"

#include <random>
#include <memory>
#include <math.h>

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
	hasRadius = initializers.radius;
	pDevice = initializers.game->getPhysicsDevice();

	return true;
}

std::unique_ptr<Object> CircleBehaviorComponent::Update()
{
	// Setup the RNG (Random Number Generator)
	static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<GAME_INT> ud(MIN_OCTOROK_ANGLE, MAX_OCTOROK_ANGLE + 1);
	static std::uniform_int_distribution<GAME_INT> randDist(MIN_OCTOROK_RADIUS, MAX_OCTOROK_RADIUS + 1);

	// Get a random distance
	GAME_FLT distance = (GAME_FLT)(randDist(e));

	// Get the body component and parts
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	GAME_FLT ang = body->getAngle();

	// Adjust the angle by random amount
	ang -= ud(e);

	// Apply linear and angular velocities 
	if (hasRadius)
	{
		GAME_VEC velocity;
		velocity.x = distance * cosf(degToRads(ang - 90));
		velocity.y = distance * sinf(degToRads(ang - 90));

		pDevice->SetLinearVelocity(_owner.get(), velocity);
	}
	pDevice->SetAngularVelocity(_owner.get(), MAX_OCTOROK_ANGLE);

	return nullptr;
}

bool CircleBehaviorComponent::Finish()
{
	return true;
}