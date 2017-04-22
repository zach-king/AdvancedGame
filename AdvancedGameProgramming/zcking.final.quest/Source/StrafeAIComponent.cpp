#include "StrafeAIComponent.h"
#include "Game.h"

#include <random>
#include <math.h>

StrafeAIComponent::StrafeAIComponent() : Component() {}

StrafeAIComponent::StrafeAIComponent(std::shared_ptr<Object> owner) : Component(owner) {}

StrafeAIComponent::~StrafeAIComponent() {}

bool StrafeAIComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	body = _owner->GetComponent<BodyComponent>();
	pDevice = inits.game->getPhysicsDevice();

	startPosition = inits.position;
	speed = inits.speed;

	return (body != nullptr && pDevice != NULL);
}

void StrafeAIComponent::Update()
{
	// Check if object should switch direciton
	GAME_VEC pos = body->getPosition();
	if (!switched && pos.x >= fminf((startPosition.x + distance), SCREEN_WIDTH - 32.0f))
	{
		switched = true;

		// Setup the RNG (Random Number Generator)
		static std::random_device rDev;
		static std::default_random_engine e(rDev());
		static std::uniform_int_distribution<GAME_INT> ud(MIN_STRAFE_DISTANCE, MAX_STRAFE_DISTANCE + 1);

		// Get random distance to move along
		distance = ud(e);
	}
	else if (switched && pos.x <= fmaxf((startPosition.x - distance), 32.0f))
	{
		switched = false;

		// Setup the RNG (Random Number Generator)
		static std::random_device rDev;
		static std::default_random_engine e(rDev());
		static std::uniform_int_distribution<GAME_INT> ud(MIN_STRAFE_DISTANCE, MAX_STRAFE_DISTANCE + 1);

		// Get random distance to move along
		distance = ud(e);
	}

	// Apply velocity change
	GAME_VEC velocity = pDevice->GetVelocity(_owner.get());
	if (switched)
		velocity.x = -1 * speed;
	else
		velocity.x = 1 * speed;

	// Now apply this modified position to the body component
	pDevice->SetLinearVelocity(_owner.get(), velocity);

	// Make sure angle stays fixed
	body->setAngle(0.0f);
}

bool StrafeAIComponent::Finish()
{
	return true;
}