#pragma once

#include "Definitions.h"
#include "Object.h"
#include "Component.h"

#include <memory>

class CircleBehaviorComponent : public Component
{
public:
	CircleBehaviorComponent();
	CircleBehaviorComponent(std::shared_ptr<Object> owner);
	~CircleBehaviorComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::unique_ptr<Object> Update();
	bool Finish();

protected:
	bool hasRadius; // if true, move in a circle; if false, just spin in place
};