/*
* Author:	Keith Bush
*			UALR
* 
* Date:		January 31, 2015	
*
* File:		GraphicsDevice.h
*
* Purpose:	Declaration of the SDL GraphicsDevice class
*/

#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Sprite.h"

class GraphicsDevice
{
		
public:

	//Constructors and Destructors
	GraphicsDevice(Uint32, Uint32);
	~GraphicsDevice();

	//Accessors
	void AddSprite(Sprite*);
	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();

	//Startup and Shutdown
	bool Initialize(bool);
	bool ShutDown();

	//Rendering functions
	void Begin();
	void Draw();
	void Present();

private:

	//Parameters
	const Uint32 SCREEN_WIDTH;
	const Uint32 SCREEN_HEIGHT;

	//Window(s) to display graphics
	SDL_Window* screen;
	SDL_Renderer* renderer;

	//Renderers
	std::vector<Sprite*> sprites;

};

#endif