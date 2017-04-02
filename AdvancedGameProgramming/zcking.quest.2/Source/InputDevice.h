#pragma once

#include <memory>
#include "SDL.h"

#include "Definitions.h"

class InputDevice
{
public:
	InputDevice();
	~InputDevice();

	SDL_Event* getEvent();
	bool Initialize();
	GAME_EVENT GetEvent();

private:
	std::unique_ptr<SDL_Event> event;
	GAME_EVENT Translate();
};
