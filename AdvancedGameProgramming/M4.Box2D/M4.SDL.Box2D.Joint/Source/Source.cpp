/*
* Author:	Keith Bush
*			UALR
* 
* Date:		March 11, 2015	
*
* File:		Source.cpp
*
* Purpose:	Demonstrate the use of Box2D joints to link two Box2D physics bodies.
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
	float dt = 1.0f/50.0f;

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
	world->SetDebugDraw(NULL);

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
	//Initialize Game Objects
	//
	GameObject* object1 = new GameObject();
	object1->Initialize(gDevice->getRenderer(),"./Assets/Images/Ball.png",world, 300, 50);

	GameObject* object2 = new GameObject();
	object2->Initialize(gDevice->getRenderer(),"./Assets/Images/Ball.png",world, 400, 150);

	//
	//Define Distance Joint (Max Distance Constraint)
	//
	//b2DistanceJointDef jd;
	//jd.bodyA = object1->getPhysicsBody();
	//jd.bodyB = object2->getPhysicsBody();
	//jd.collideConnected = true;
	//jd.localAnchorA = jd.bodyA->GetLocalCenter();
	//jd.localAnchorB = jd.bodyB->GetLocalCenter();
 //   jd.length = RW2PW(141.0f);

	//
	//Define Rope Joint (Max Distance Constraint)
	//
	b2RopeJointDef jd;
	jd.maxLength = RW2PW(141.0f);
	jd.bodyA = object1->getPhysicsBody();
	jd.bodyB = object2->getPhysicsBody();
	jd.collideConnected = true;
	jd.localAnchorA = jd.bodyA->GetLocalCenter();
	jd.localAnchorB = jd.bodyB->GetLocalCenter();

	//Add the joint to the physics world
	world->CreateJoint(&jd);


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
		object1->HandleEvent(event);
		object2->HandleEvent(event);

		//
		//Conduct the Game Logic update (i.e., physics/animation)
		//
		object1->Update(dt);
		object2->Update(dt);

		//
		//Conduct Physics update
		//
		world->Step(dt, 8, 3);

		//
		//Game state updates complete, let's draw
		//
		gDevice->Begin();

		//Draw a game object
		object1->Draw();
		object2->Draw();

		//End the frame and draw to window
		gDevice->Present();

		//Buffer the Frames per second (if necessary)
		fps->fpsRegulate();

		//SDL_Delay(4000);// DEBUG

	}

	return 0;

}