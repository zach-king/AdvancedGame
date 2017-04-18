#include "SpinComponent.h"
#include "Object.h"
#include "Game.h"

#include <random>

SpinComponent::SpinComponent() : Component()
{
}

SpinComponent::SpinComponent(std::shared_ptr<Object> owner) : Component(owner)
{
}

SpinComponent::~SpinComponent()
{
}

bool SpinComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	pDevice = inits.game->getPhysicsDevice();

	// Randomize the rotation speed
	static std::random_device rd;
	static std::default_random_engine e(rd());
	static std::uniform_real_distribution<> spinDist(MIN_ASTEROID_SPIN_SPEED, MAX_ASTEROID_SPIN_SPEED);
	speed = spinDist(e);

	// Apply angular velocity
	pDevice->SetAngularVelocity(_owner.get(), speed);

	return true;
}

void SpinComponent::Update()
{

}

bool SpinComponent::Finish()
{
	return true;
}