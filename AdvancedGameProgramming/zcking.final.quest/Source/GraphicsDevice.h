#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <memory>
#include <vector>

class SpriteComponent;

class GraphicsDevice
{
public:
	GraphicsDevice(Uint32, Uint32);
	~GraphicsDevice();

	// Accessors
	void AddSprite(SpriteComponent *);
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

	// Startup and shutdown
	bool Initialize(bool);
	bool Shutdown();

	// Rendering functions
	void Begin();
	void Draw();
	void Present();

	void DrawText(std::string, int);
	void setFont(std::string, int);

private:
	// Window(s) to display graphics
	SDL_Window* screen;
	SDL_Renderer* renderer;

	// Parameters
	const Uint32 SCREEN_WIDTH;
	const Uint32 SCREEN_HEIGHT;

	// Global font to use with text rendering
	TTF_Font *font;

	// Renderers
	std::vector<SpriteComponent *> sprites;

	// Tmp texture for drawing UI text
	SDL_Texture* tmpTex;
};
