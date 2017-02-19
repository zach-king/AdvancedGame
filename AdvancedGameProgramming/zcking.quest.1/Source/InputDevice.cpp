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
	return (event != nullptr);
}

GAME_EVENT InputDevice::GetEvent()
{
	// Poll event
	SDL_PollEvent(event.get());

	return Translate();
}

GAME_EVENT InputDevice::Translate()
{
	// Translate Event to GAME_EVENT
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_LEFT:
			return GAME_LEFT;
		case SDLK_RIGHT:
			return GAME_RIGHT;
		case SDLK_UP:
			return GAME_UP;
		case SDLK_DOWN:
			return GAME_DOWN;
		}
		break;
	case SDL_KEYUP:
		return GAME_NA;
	case SDL_QUIT:
		return GAME_QUIT;
	default:
		return GAME_NA;
		break;
	}
}