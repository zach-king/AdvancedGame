#pragma once

#include "Component.h"
#include "Object.h"

#include <memory>

class SlideBehaviorComponent : public Component
{
public:
	SlideBehaviorComponent();
	SlideBehaviorComponent(std::shared_ptr<Object> owner);
	~SlideBehaviorComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::unique_ptr<Object> Update();
	bool Finish();

protected:

};