#pragma once

#include "InputDevice.h"
#include "Definitions.h"

class View
{
public:
	View();
	~View();
	bool Initialize(InputDevice*, GAME_FLT, GAME_FLT);
	bool Update(GAME_FLT);
	GAME_VEC getPosition();
	GAME_FLT getAngle();
	GAME_VEC getCenter();

private:
	InputDevice* iDevice;
	GAME_VEC position;
	GAME_VEC center;
	GAME_FLT angle;
};