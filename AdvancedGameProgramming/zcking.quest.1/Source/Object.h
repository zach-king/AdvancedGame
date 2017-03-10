#pragma once

#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Definitions.h"
#include "View.h"
#include "Texture.h"
#include <SDL.h>

#include <string>
#include <memory>

class Texture;

// Base class for objects to inherit from 
class Object
{
public:
	// Default constructor/destructor
	Object();
	~Object();

	// Initializer (renderer, path to texture)
	bool Initialize(SDL_Renderer*, std::string);

	// Pure virtual methods for their movement and drawing
	virtual void Update() = 0;
	virtual void Draw(View*) = 0;

	// Setters
	void setStartPosition(GAME_VEC);
	void setPosition(GAME_VEC);
	void setAngle(GAME_FLT);

	// Getter for position
	GAME_VEC getPosition();

protected:
	// SDL Renderer pointer
	SDL_Renderer* renderer;

	// Graphics and Input Device pointers
	GraphicsDevice* gDevice;
	InputDevice* iDevice;

	// Texture for the object
	std::unique_ptr<Texture> texture;

	// Position and angle members for movement
	GAME_VEC position;
	GAME_VEC startPosition;
	GAME_FLT angle;
};