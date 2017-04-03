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
	bool GetEvent(GAME_EVENT event);

private:
	std::unique_ptr<SDL_Event> event;

	std::vector<bool> keyFlags;
};
