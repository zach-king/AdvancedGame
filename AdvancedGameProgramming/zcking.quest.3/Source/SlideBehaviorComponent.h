#pragma once

#include "Definitions.h"
#include "Object.h"
#include "Component.h"
#include "PhysicsDevice.h"

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
	bool vertical;			// whether or not we should move vertical or horizontal
	GAME_FLT distance;		// the distance to move (which gets randomized)
	GAME_VEC startPosition; // stores the starting position so we know when to change direction
	bool switched;			// flag for help with switching directions
	PhysicsDevice* pDevice;
};