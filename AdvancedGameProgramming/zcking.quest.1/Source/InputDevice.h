#pragma once

#include <memory>
#include <SDL.h>

#include "Definitions.h"

class InputDevice
{
public:
	// Default constructor/deconstructor
	InputDevice();
	~InputDevice();

	// Intializer (creates the SDL_Event)
	bool Initialize();

	// Gets a Game Event
	GAME_EVENT GetEvent();

private:
	// SDL Event pointer
	std::unique_ptr<SDL_Event> event;

	// Translates SDL Event to Game Event
	GAME_EVENT Translate();
};
