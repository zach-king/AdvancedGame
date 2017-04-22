/*
* Author:	Zachary King
*			UALR
* 
* Date:		April, 2017	
*
* File:		Source.cpp
*/

#include <iostream>
#include <random>
#include <memory>

#include "SDL.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	//========================================
	//Construct Game
	//========================================
	std::unique_ptr<Game> game(std::make_unique<Game>());
	if(!game->Initialize())
	{
		printf( "Game could not Initialize!");
		exit(1);
	}

	//========================================
	//Load Level
	//========================================
	//game->Reset();
	std::string levelConfigFile= "./Assets/Config/boss.xml";
	std::string objectConfigFile = "./Assets/Config/objects.xml";
	std::string physicsConfigFile = "./Assets/Config/physics.xml";
	std::string audioConfigFile = "./Assets/Config/audio.xml";
	if(!game->LoadLevel(levelConfigFile, objectConfigFile, physicsConfigFile, audioConfigFile))
	{
		printf( "Game could not load level %s: ", levelConfigFile.c_str());
		exit(1);
	}

	//========================================
	//Main Game Loop
	//========================================
	bool quit = false;

	//While the user hasn't quit
	while(!game->Run()){ }

	//========================================
	// Clean-up
	//========================================
	if(game)
	{
		game = nullptr;
	}

	return 0;
}