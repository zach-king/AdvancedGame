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
	bool Initialize(SDL_Renderer*,std::string,float,float,float,float,int);
	void Update();
	void Draw();
    bool isDead();

protected:
	SDL_Renderer* renderer;
	Texture* texture;

    //Position
	float xPosition;
	float yPosition;

    //Motion
    float xVelocity;
    float yVelocity;

    //Transparency
    int alpha;
    int dAlpha;

    //Garbage Collection
    bool dead;
};

#endif