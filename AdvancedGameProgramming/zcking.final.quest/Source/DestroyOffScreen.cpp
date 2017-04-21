#include "DestroyOffScreen.h"

DestroyOffScreen::DestroyOffScreen() : OffScreenComponent() {}

DestroyOffScreen::DestroyOffScreen(std::shared_ptr<Object> owner) : OffScreenComponent(owner) {}

DestroyOffScreen::~DestroyOffScreen() {}

void DestroyOffScreen::Trigger()
{
	// Set is dead
	_owner->setIsDead(true);
}