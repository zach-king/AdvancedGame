#pragma once

#include <memory>
#include <vector>

#include "SDL.h"
#include "Definitions.h"

class InputDevice
{
public:
	InputDevice();
	~InputDevice();

	bool Initialize();
	void Update();
	bool GetEvent(GAME_EVENT event); // Return whether or not an event is currently set

private:
	// SDL Event to be polled
	std::unique_ptr<SDL_Event> event;

	// Vector of flags (bools) for keys being up or down
	std::vector<bool> keyFlags;
};
