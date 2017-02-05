/*
* Author:	Sean Orme
*			UALR
* 
* Date:		February 2, 2016	
*
* File:		Source.cpp
*
* Purpose:	This programming task examines the following concepts
*				- Abstraction of game devices (Graphics, Input) from SDL Library
*               - AssetManagement using Libraries
*               - Object Factory Design Pattern
*               - XML Construction of 2-D game system
*               - Main Game Loop
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
	game->Reset();
	std::string levelConfigFile= "./Assets/Config/level2.xml";
	std::string objectConfigFile = "./Assets/Config/objects.xml";
	if(!game->LoadLevel(levelConfigFile, objectConfigFile))
	{
		printf( "Game could not load level %s: ", levelConfigFile.c_str());
		exit(1);
	}

	//========================================
	//Main Game Loop
	//========================================
	bool quit = false;

	//While the user hasn't quit
	while(!game->Run()){	}

	//========================================
	// Clean-up
	//========================================
	if(game)
	{
		game = nullptr;
	}


	return 0;

}