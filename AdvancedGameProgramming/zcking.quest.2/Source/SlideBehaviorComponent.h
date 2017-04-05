#pragma once

#include "Component.h"
#include "Object.h"
#include "Definitions.h"

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
	bool vertical;
	GAME_FLT distance;
	GAME_VEC startPosition;
	bool switched;
};