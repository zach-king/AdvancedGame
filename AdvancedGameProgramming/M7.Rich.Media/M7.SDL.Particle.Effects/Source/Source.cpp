/*
* Author:	Keith Bush
*			UALR
* 
* Date:		January 31, 2015	
*
* File:		Source.cpp
*
* Purpose:	Demonstrate initializing SDL, generating an empty graphics window, and
*			gracefully shutting down the program.
*/

#include <iostream>
#include <vector>

#include "SDL.h"
#include "GraphicsDevice.h"
#include "Timer.h"
#include "GameObject.h"


float GenRandFloat(float minv, float maxv){
	float value = (float)rand();
	value /= RAND_MAX;
	value = (maxv-minv)*value+minv;
	//std::cout << value << std::endl;
	return(value);
}

int main(int argc, char *argv[])
{

	//Construct Graphical Device
	GraphicsDevice* gDevice = new GraphicsDevice(800,600);
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
	if(!fps->Initialize(100)){
		printf( "Frame Timer could not initialize! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}


	std::vector<GameObject*> particles;
	int x,y;
	float dx, dy, vx, vy, da;


	//Initialize mouse coordinates
	x = 400;
	y = 300;

	//Initialize Termination Criteria
	bool quit = false;

	//While the user hasn't quit
	while(quit == false)
	{

		//Start the frame's time
		fps->start();

		//Poll Event
		SDL_PollEvent( event );

		//Translate Event to QUIT signal
		if(event->type == SDL_QUIT)
		{
			quit=true;
		}

		if(event->type==SDL_MOUSEMOTION){
			//Get coordinates of the event
			x = event->motion.x;
			y = event->motion.y;
		}

		//Number of particles
		int Nparticles = 10;       //Number of particles generate per frame

		//Spread around point source
		float radius = 15.0f;      //width/height of box of random initialization

		//X velocity
		float yVelMin = -1.0f;
		float yVelMax = 1.0f;

		//Y velocity
		float xVelMin = -1.0f;
		float xVelMax = 1.0f;

		//Decay rate
		float aRateMin = 3.0f;
		float aRateMax = 4.0f;

		//Init, construct, and load particles into Game System
		for(int i=0;i<Nparticles;i++){

			//Randomize x,y and velocities around the mouse cursor
			dx=GenRandFloat(-radius,radius); //random x-axis offset from cursor
			dy=GenRandFloat(-radius,radius); //random y-axis offset from cursor
			vx=GenRandFloat(xVelMin,xVelMax);     //x-axis velocity
			vy=GenRandFloat(yVelMin,yVelMax);     //y-axis velocity
			da=GenRandFloat(aRateMin,aRateMax);     //Decay rate of opaqueness

			//Construct and add the particle to the game system
			GameObject* particle = new GameObject();
			particle->Initialize(gDevice->getRenderer(),"./Assets/Images/paint_dot.png",(float)(x+dx),(float)(y+dy),vx,vy,(int)da);
			particles.push_back(particle);
		}

		//Create an interator
		std::vector<GameObject*>::iterator viter;

		//Update the particles
		for(viter=particles.begin();viter!=particles.end();viter++){
			(*viter)->Update();
		}

		//Remove dead particles
		for(viter=particles.begin();viter!=particles.end(); /*empty*/){
			if((*viter)->isDead()){
				delete (*viter);
				viter = particles.erase(viter);
			}else{
				viter++;
			}
		}


        //----------------------------
        // OUTPUT
        //----------------------------

		//Start the frame
		gDevice->Begin();

        //Draw the particles
		for(viter=particles.begin();viter!=particles.end();viter++){
			(*viter)->Draw();
		}

		//End the frame and draw to window
		gDevice->Present();

		//Buffer the Frames per second (if necessary)
		fps->fpsRegulate();

	}


	return 0;

}