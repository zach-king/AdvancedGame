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

#include "SDL.h"
#include "SDL_Mixer.h"
#include "GraphicsDevice.h"
#include "Timer.h"
#include "GameObject.h"

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

    //----------------------------------------------
    // BEGIN MIXER INIT 
    //----------------------------------------------

    //Load the Mixer subsystem
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096 ) <0)
	{
		printf( "SDL Mixer could not initialize! SDL_Error: %s\n", Mix_GetError() );
		exit(1);	    		
	}

	//The sound effects that will be used
	Mix_Chunk *left = Mix_LoadWAV( "./Assets/Sounds/scratch.wav");
	Mix_Chunk *right = Mix_LoadWAV( "./Assets/Sounds/high.wav" );

    //The background music
   	Mix_Music *music = Mix_LoadMUS( "./Assets/Sounds/beat.wav" );

    //Mixing parameters
    int numChannels = 100; //Number of concurrent channels to mix
    int channelID = -1; //Select first available channel
    int numLoops = 0; //Number of times to repeat the chunk in a channel.

    //Allocate sufficient channels
    Mix_AllocateChannels(numChannels);

    //Start the background music
   	Mix_PlayMusic(music,-1); //-1 is repeat forever

    //----------------------------------------------
    // END MIXER INIT 
    //----------------------------------------------

	//Initialize
	GameObject* object = new GameObject();
	object->Initialize(gDevice->getRenderer(),"./Assets/Images/PlayerPaper.png");

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

		//
		//Object handles relevant events
		//
		object->HandleEvent(event);


		//
		//Mixer responds to relevant events
		//
		if(event->type == SDL_KEYDOWN)
		{
			switch(event->key.keysym.sym )
			{

			case SDLK_LEFT: 

				//Play Sound 
				Mix_PlayChannel(channelID, left, numLoops);

				break;
			case SDLK_RIGHT:

				//Play Sound
				Mix_PlayChannel(channelID, right,numLoops);

			}
		}


		//
		//Object update
		//
		object->Update();

		//Start the frame
		gDevice->Begin();

		//Draw a game object
		object->Draw();

		//End the frame and draw to window
		gDevice->Present();

		//Buffer the Frames per second (if necessary)
		fps->fpsRegulate();

	}


   	//Free the sound effects
    Mix_FreeChunk( left);
    Mix_FreeChunk( right );
    
    //Quit SDL_mixer
    Mix_CloseAudio();

	return 0;

}