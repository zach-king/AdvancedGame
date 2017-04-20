#include "OffScreenComponent.h"
#include "Game.h"

OffScreenComponent::OffScreenComponent() : Component() {}

OffScreenComponent::OffScreenComponent(std::shared_ptr<Object> owner) : Component(owner)
{

}

OffScreenComponent::~OffScreenComponent()
{

}

bool OffScreenComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	body = _owner->GetComponent<BodyComponent>();
	return (body != nullptr);
}

void OffScreenComponent::Update()
{
	// Check if off screen
	GAME_VEC pos = body->getPosition();

	// Don't count objects "above" the screen since in this game they move down
	if (pos.y > SCREEN_HEIGHT)
	{
		Trigger(); // call the trigger method
	}
}

bool OffScreenComponent::Finish()
{
	return true;
}



