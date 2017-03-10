/*
* Author:	Keith Bush
*			UALR
* 
* Date:		January 31, 2015	
*
* File:		GraphicsDevice.cpp
*
* Purpose:	Definition of the SDL GraphicsDevice class
*/

#include<iostream>
#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice(Uint32 width, Uint32 height) : SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{
	screen = NULL;
	renderer = NULL;
}

GraphicsDevice::~GraphicsDevice()
{
	if(!ShutDown())
	{
		printf( "SDL could not shut down! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}
}

SDL_Window* GraphicsDevice::GetWindow()
{
	return(screen);
}

bool GraphicsDevice::Initialize(bool fullScreen)
{

	//Initialize all SDL subsystems
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return(false);
	}

	//Initialize SDL_image subsystems
	if(!IMG_Init(IMG_INIT_PNG))
	{
		printf( "SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError() );
		return(false);
	}

	//Initialize SDL_ttf subsystems
	if(TTF_Init()==-1)
	{
		printf( "SDL_ttf could not initialize! SDL_Error: %s\n", TTF_GetError() );
		return(false);
	}

	if(!fullScreen)
	{
		//Construct and check window construction
		screen = SDL_CreateWindow("Demonstration Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		screen = SDL_CreateWindow("Demonstration Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	}
	if(screen==NULL)
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return(false);
	}

	//Construct the renderer
	renderer = SDL_CreateRenderer(screen,-1,SDL_RENDERER_ACCELERATED);
	if(renderer==NULL)
	{
		printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
		return(false);
	}

	//Set the background color (default)
	SDL_SetRenderDrawColor(renderer,0,0,0,255);

	return(true);

}

bool GraphicsDevice::ShutDown()
{
	//Free the window
	SDL_DestroyWindow(screen);
	screen = NULL;

	//Free renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Quit SDL Subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return(true);
}




void GraphicsDevice::Begin()
{
	SDL_RenderClear(renderer);
}

void GraphicsDevice::Draw()
{
	for(auto sprite : sprites)
	{
		sprite->Draw();
	}
}

void GraphicsDevice::Present()
{
	SDL_RenderPresent(renderer);
}

SDL_Renderer* GraphicsDevice::GetRenderer()
{
	return(renderer);
}

void GraphicsDevice::AddSprite(Sprite* sprite)
{
	sprites.push_back(sprite);
}