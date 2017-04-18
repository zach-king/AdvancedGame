#include "LinearMoveComponent.h"
#include "Object.h"
#include "Game.h"

#include <math.h>


LinearMoveComponent::LinearMoveComponent() : Component()
{
}

LinearMoveComponent::LinearMoveComponent(std::shared_ptr<Object> owner) : Component(owner)
{
	speed = 0;
}

LinearMoveComponent::~LinearMoveComponent()
{
}

bool LinearMoveComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	// Grab attributes
	pDevice = inits.game->getPhysicsDevice();
	speed = inits.speed;

	return true;
}

void LinearMoveComponent::Update()
{
	pDevice->SetLinearVelocity(_owner.get(), { VEC_UP.x * speed, VEC_UP.y * speed });
}

bool LinearMoveComponent::Finish()
{
	return true;
}

GAME_FLT LinearMoveComponent::getSpeed()
{
	return this->speed;
}

void LinearMoveComponent::setSpeed(GAME_FLT spd)
{
	this->speed = spd;
}