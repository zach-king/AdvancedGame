#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Box2D/Box2D.h"

class Texture;

class GameObject
{
public:
	GameObject();
	~GameObject();
	bool Initialize(SDL_Renderer*,std::string,b2World* world);
	void HandleEvent(SDL_Event*);
	void Update(float);
	void Draw();
    
     b2Body* getPhysicsBody();

protected:
	
    //Graphics Components
	SDL_Renderer* renderer;
	Texture* texture;
	
    //Box2D Physics Components
    b2BodyDef bd;
    b2PolygonShape shape;
    b2FixtureDef shapefd;
    b2Body* body;

    //Event-handling feedback
   	std::string command;
	TTF_Font* font;

    bool initialized;

};

#endif