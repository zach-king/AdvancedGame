#include "CircleBehaviorComponent.h"
#include "BodyComponent.h"
#include "GameFunctions.h"

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

	return true;
}

std::unique_ptr<Object> CircleBehaviorComponent::Update()
{
	// Setup the RNG (Random Number Generator)
	static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<GAME_INT> ud(MIN_OCTOROK_ANGLE, MAX_OCTOROK_ANGLE + 1);
	static std::uniform_int_distribution<GAME_INT> randDist(MIN_OCTOROK_RADIUS, MAX_OCTOROK_RADIUS + 1);

	GAME_FLT distance = (GAME_FLT)(randDist(e));

	// Get the body component and parts
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	GAME_FLT ang = body->getAngle();
	GAME_VEC pos = body->getPosition();

	// Adjust the angle by random amount
	ang -= ud(e);

	// Check if spinning or moving in circle
	if (hasRadius)
	{
		// Modify the position too
		pos.x += distance * cosf(degToRads(ang - 90)); // cos for x component
		pos.y += distance * sinf(degToRads(ang - 90)); // sin for y component
		body->setPosition(pos); // apply modified position
	}

	body->setAngle(ang); // apply modified angle

	return nullptr;
}

bool CircleBehaviorComponent::Finish()
{
	return false;
}