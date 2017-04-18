#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<iostream>
#include "SDL.h"

class Texture;

class GameObject
{
public:
	GameObject();
	~GameObject();
	bool Initialize(SDL_Renderer*,std::string);
	void HandleEvent(SDL_Event* event);
	void Update();
	void Draw();

protected:
	SDL_Renderer* renderer;
	Texture* texture;

	float xPosition;
	float yPosition;
	float angle;
	float commandAngle;
};

#endif