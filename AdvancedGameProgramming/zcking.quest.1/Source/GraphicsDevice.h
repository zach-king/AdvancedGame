#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <memory>

class GraphicsDevice
{
public:
	// Constructor and destructor
	GraphicsDevice(Uint32, Uint32);
	~GraphicsDevice();

	// Initializer(fullscreen)
	bool Initialize(bool);
	bool Shutdown(); // Shuts down subsystems and device
	void Begin();
	void Present();

	// Getter for the renderer
	SDL_Renderer* getRenderer();

private:
	// Window(s) to display graphics
	SDL_Window* screen;
	SDL_Renderer* renderer;

	// Parameters
	const Uint32 SCREEN_WIDTH;
	const Uint32 SCREEN_HEIGHT;
};
