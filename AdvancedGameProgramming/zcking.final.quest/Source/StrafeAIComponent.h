#pragma once

#include "Component.h"
#include "BodyComponent.h"
#include "PhysicsDevice.h"

class StrafeAIComponent : public Component
{
public:
	StrafeAIComponent();
	StrafeAIComponent(std::shared_ptr<Object> owner);
	~StrafeAIComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	void Update();
	bool Finish();

private:
	std::shared_ptr<BodyComponent> body;
	PhysicsDevice* pDevice;
	bool switched;
	GAME_VEC startPosition;
	GAME_FLT distance;
	GAME_FLT speed;
};