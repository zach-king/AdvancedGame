#pragma once

#include "Definitions.h"
#include "Object.h"
#include "Component.h"
#include "ObjectFactory.h"
#include "InputDevice.h"
#include "PhysicsDevice.h"

#include <memory>

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent();
	PlayerInputComponent(std::shared_ptr<Object> owner);
	~PlayerInputComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::unique_ptr<Object> Update();
	bool Finish();

protected:
	InputDevice* iDevice;
	ObjectFactory* oFactory;
	PhysicsDevice* pDevice;
	GAME_OBJECTFACTORY_INITIALIZERS arrowInits;

	// For advanced shooting of Link's arrows
	bool canFire;
	GAME_INT reloadFrames; // can specify how fast player can shoot
	GAME_FLT fireAngle;
};