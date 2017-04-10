#include "SlideBehaviorComponent.h"
#include "BodyComponent.h"
#include "Game.h"

#include <random>
#include <memory>

SlideBehaviorComponent::SlideBehaviorComponent() : Component()
{
}

SlideBehaviorComponent::SlideBehaviorComponent(std::shared_ptr<Object> owner) : Component(owner)
{
	switched = false;
}

SlideBehaviorComponent::~SlideBehaviorComponent()
{
}

bool SlideBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	vertical = initializers.verticalSlide;
	startPosition = initializers.position;
	pDevice = initializers.game->getPhysicsDevice();

	// Setup the RNG (Random Number Generator)
	static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<GAME_INT> ud(MIN_LEEVER_DISTANCE, MAX_LEEVER_DISTANCE + 1);

	// Get random distance to move along
	distance = ud(e);

	return true;
}

std::unique_ptr<Object> SlideBehaviorComponent::Update()
{
	// Grab the body component and position
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	GAME_VEC pos = body->getPosition();

	// Switch direction when needed
	if (vertical)
	{
		if (pos.y >= (startPosition.y + distance))
			switched = true;
		if (pos.y <= (startPosition.y - distance))
			switched = false;
	} 
	else
	{
		if (pos.x >= (startPosition.x + distance))
			switched = true;
		if (pos.x <= (startPosition.x - distance))
			switched = false;
	}

	// Based off direction, change velocity
	GAME_VEC velocity;
	if (vertical && switched)
		velocity = { 0, -1 * DEFAULT_LEEVER_SPEED };
	else if (vertical && !switched)
		velocity = { 0, DEFAULT_LEEVER_SPEED };
	else if (!vertical && switched)
		velocity = { -1 * DEFAULT_LEEVER_SPEED, 0 };
	else if (!vertical && !switched)
		velocity = { 1 * DEFAULT_LEEVER_SPEED, 0 };

	// Now apply this modified position to the body component
	pDevice->SetLinearVelocity(_owner.get(), velocity);

	return nullptr;
}

bool SlideBehaviorComponent::Finish()
{
	return true;
}