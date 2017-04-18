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

//Manipulate the sound's volume within [min,max]
int updateSound(int minVal, int maxVal, int curValue, int increment)
{
	int value = curValue+increment;

	if(value>=maxVal)
	{
		value=maxVal;
	}

	if(value<=minVal)
	{
		value=minVal;
	}	

	return(value);
}

//Manipulate the angle of the sound's source [0,360)
int updateSoundDirection(int minVal, int maxVal, int curValue, int increment)
{
	int value = curValue+increment;

	if(value>maxVal)
	{
		value = minVal+increment;
	}

	if(value<minVal)
	{
		value = maxVal+increment;
	}

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
	if(!fps->Initialize(10)){
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
	Mix_Chunk *sound = Mix_LoadWAV( "./Assets/Sounds/high.wav" );

	//Mixing parameters
	int numChannels = 1; //Number of concurrent channels to mix
	int channelID = 0; //Select first available channel
	int numLoops = 0; //Number of times to repeat the chunk in a channel.

	//Allocate sufficient channels
	Mix_AllocateChannels(numChannels);

	//Initialize effect manipulation params
	Uint8 maxVolume = 255;//sound->volume;
	int soundDirection = 0;
	int soundDistance = (int)((float)maxVolume/2);
	int distanceIncrement = 5;
	int directionIncrement = 5;

   	//Init Panning
	Mix_SetPanning(channelID,maxVolume,0);

	//----------------------------------------------
	// END MIXER INIT 
	//----------------------------------------------

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


		if(event->type == SDL_KEYDOWN)
		{
			switch(event->key.keysym.sym )
			{

       		//
		    //Sound state responds to relevent events
		    //     
			case SDLK_LEFT: 
				soundDirection = updateSoundDirection(0,360,soundDirection,-directionIncrement);
				break;
			case SDLK_RIGHT:
				soundDirection = updateSoundDirection(0,360,soundDirection,directionIncrement);
				break;  
			case SDLK_UP:
				soundDistance = updateSound(1,maxVolume,soundDistance,-distanceIncrement);
				break;
			case SDLK_DOWN:
				soundDistance = updateSound(1,maxVolume,soundDistance,distanceIncrement);
				break;
			default: break;
			}

            //View sound state
            std::cout << soundDirection << ", " << soundDistance << std::endl;

            //Set the sound distance and director for effect
			Mix_SetPosition(channelID,(Sint16)soundDirection,(Uint8)soundDistance);

            //Play the sound as configured above
    	    Mix_PlayChannel(channelID, sound, numLoops);
	
		}

   		//Start the frame
		gDevice->Begin();

		//End the frame and draw to window
		gDevice->Present();

		//Buffer the Frames per second (if necessary)
		fps->fpsRegulate();

	}

	//Free the sound effects
	Mix_FreeChunk(sound);

	//Quit SDL_mixer
	Mix_CloseAudio();

	return 0;

}