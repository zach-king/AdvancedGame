#include "InputDevice.h"

InputDevice::InputDevice()
{

}

InputDevice::~InputDevice()
{

}

bool InputDevice::Initialize()
{
	// Construct Event
	event = std::make_unique<SDL_Event>();

	// Push false for each game event
	for (int ev = GAME_NA; ev != GAME_QUIT; ev++)
	{
		keyFlags.push_back(false);
	}

	return (event != nullptr);
}

void InputDevice::Update()
{
	// Poll event
	SDL_PollEvent(event.get());
	
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_m:
			keyFlags[GAME_MAP_TOGGLE] = true;
			break;
		case SDLK_LEFT:
			keyFlags[GAME_LEFT] = true;
			break;
		case SDLK_RIGHT:
			keyFlags[GAME_RIGHT] = true;
			break;
		case SDLK_UP:
			keyFlags[GAME_UP] = true;
			break;
		case SDLK_DOWN:
			keyFlags[GAME_DOWN] = true;
			break;
		case SDLK_w:
			keyFlags[GAME_NORTH] = true;
			break;
		case SDLK_a:
			keyFlags[GAME_WEST] = true;
			break;
		case SDLK_s:
			keyFlags[GAME_SOUTH] = true;
			break;
		case SDLK_d:
			keyFlags[GAME_EAST] = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym)
		{
		case SDLK_m:
			keyFlags[GAME_MAP_TOGGLE] = false;
			break;
		case SDLK_LEFT:
			keyFlags[GAME_LEFT] = false;
			break;
		case SDLK_RIGHT:
			keyFlags[GAME_RIGHT] = false;
			break;
		case SDLK_UP:
			keyFlags[GAME_UP] = false;
			break;
		case SDLK_DOWN:
			keyFlags[GAME_DOWN] = false;
			break;
		case SDLK_w:
			keyFlags[GAME_NORTH] = false;
			break;
		case SDLK_a:
			keyFlags[GAME_WEST] = false;
			break;
		case SDLK_s:
			keyFlags[GAME_SOUTH] = false;
			break;
		case SDLK_d:
			keyFlags[GAME_EAST] = false;
			break;
		}
		break;
	case SDL_QUIT:
		keyFlags[GAME_QUIT] = true;
	default:
		keyFlags[GAME_NA] = true;
		return;
		break;
	}

	// If didn't return after default: 
	// Then GAME_NA should be false
	keyFlags[GAME_NA] = false;
}

bool InputDevice::GetEvent(GAME_EVENT ev)
{
	return keyFlags[ev];
}
