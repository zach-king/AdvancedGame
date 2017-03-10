#pragma once

#include "InputDevice.h"
#include "Definitions.h"

class View
{
public:
	// Default constructor/destructor
	View();
	~View();

	// Initialize the view, store pointers and position
	bool Initialize(InputDevice*, GAME_FLT, GAME_FLT);

	// Update position based off user input
	bool Update(GAME_FLT);

	// Getters
	GAME_VEC getPosition();
	GAME_FLT getAngle();
	GAME_VEC getCenter();

private:
	// Members
	InputDevice* iDevice;
	GAME_VEC position;
	GAME_VEC center;
	GAME_FLT angle;
};