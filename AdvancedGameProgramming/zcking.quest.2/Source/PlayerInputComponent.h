#pragma once

#include "Component.h"
#include "Object.h"
#include "Definitions.h"
#include "InputDevice.h"

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
};