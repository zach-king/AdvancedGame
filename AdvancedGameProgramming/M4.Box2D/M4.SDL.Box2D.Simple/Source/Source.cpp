/*
* Author:	Keith Bush
*			UALR
* 
* Date:		March 1, 2015	
*
* File:		Source.cpp
*
* Purpose:	Demontrate the inclusion of a physics body into a game object.
*/

#include <iostream>
#include "SDL.h"
#include "GraphicsDevice.h"
#include "Timer.h"
#include "GameObject.h"
#include "GameFunctions.h"
#include "Box2D/Box2D.h"

int main(int argc, char *argv[])
{

    //Screen dimensions
    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 600;

    //Time per frame
    float dt = 1.0/50.0f;

	//Construct Graphical Device
	GraphicsDevice* gDevice = new GraphicsDevice(SCREEN_WIDTH, SCREEN_HEIGHT);
	if(!gDevice->Initialize(true))
	{
		printf( "Graphics Device could not initialize! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}

	//Construct Event
	SDL_Event* event = new SDL_Event();
	if(!event){
		printf( "SDL Event could not initialize! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}

	//Construct Frame Timer
	Timer* fps = new Timer();
	if(!fps->Initialize((Uint32)1/dt)){
		printf( "Frame Timer could not initialize! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}

    //
    //Construct Physics World
    //
    const b2Vec2 gravity(RW2PW(0),RW2PW(+200));
	b2World* world = new b2World(gravity);

	//Set boundaries of world (Render->Physics)
	const b2Vec2 vTopLeft = b2Vec2(RW2PW(0),RW2PW(0));
	const b2Vec2 vTopRight = b2Vec2(RW2PW(SCREEN_WIDTH),RW2PW(0));
	const b2Vec2 vBottomLeft = b2Vec2(RW2PW(0),RW2PW(SCREEN_HEIGHT));
	const b2Vec2 vBottomRight = b2Vec2(RW2PW(SCREEN_WIDTH),RW2PW(SCREEN_HEIGHT));

    //
	//Create the world boundaries
    //
	b2BodyDef bd;
	b2Body* edge = world->CreateBody(&bd);
	b2EdgeShape shape;

	//Set-up debuggin
	//world->SetDebugDraw(NULL);

	//Create bottom boundary
	shape.Set(vBottomLeft,vBottomRight);
	edge->CreateFixture(&shape,0);

	//Create left boundary
	shape.Set(vBottomLeft,vTopLeft);
	edge->CreateFixture(&shape,0);

	//Create right boundary
	shape.Set(vBottomRight,vTopRight);
	edge->CreateFixture(&shape,0);

    //
	//Initialize Game Object
    //
	GameObject* object = new GameObject();
	object->Initialize(gDevice->getRenderer(),"./Assets/Images/PlayerPaper.png",world);

	//Initialize Termination Criteria
	bool quit = false;

	//While the user hasn't quit
	while(!quit)
	{

		//Start the frame's time
		fps->start();

		//Check for an event
		if(SDL_PollEvent( event ))
		{
			//Translate Event to QUIT signal
			if(event->type == SDL_QUIT)
			{
				quit=true;
			}
		}

		//
		//Object handles relevant events
		//
		object->HandleEvent(event);

		//
		//Conduct the Game Logic update (i.e., physics/animation)
		//
		object->Update(dt);

        //
        //Conduct Physics update
        //
        world->Step(dt, 8, 3);

		//
		//Game state updates complete, let's draw
		//
		gDevice->Begin();

		//Draw a game object
		object->Draw();

		//End the frame and draw to window
		gDevice->Present();

		//Buffer the Frames per second (if necessary)
		fps->fpsRegulate();

	}

	return 0;

}