#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <memory>

class GraphicsDevice
{
public:
	GraphicsDevice(Uint32, Uint32);
	~GraphicsDevice();

	bool Initialize(bool);
	bool Shutdown();
	void Begin();
	void Present();

	SDL_Renderer* getRenderer();

private:
	// Window(s) to display graphics
	SDL_Window* screen;
	SDL_Renderer* renderer;

	// Parameters
	const Uint32 SCREEN_WIDTH;
	const Uint32 SCREEN_HEIGHT;
};
