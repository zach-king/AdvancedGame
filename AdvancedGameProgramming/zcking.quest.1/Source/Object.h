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

class Object
{
public:
	Object();
	~Object();
	bool Initialize(SDL_Renderer*, std::string);

	virtual void Update() = 0;
	virtual void Draw(View*) = 0;
	void setStartPosition(GAME_VEC);
	void setPosition(GAME_VEC);
	void setAngle(GAME_FLT);
	GAME_VEC getPosition();

protected:
	SDL_Renderer* renderer;
	GraphicsDevice* gDevice;
	InputDevice* iDevice;
	std::unique_ptr<Texture> texture;
	GAME_VEC position;
	GAME_VEC startPosition;
	GAME_FLT angle;
};