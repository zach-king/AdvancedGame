#pragma once

class GraphicsDevice;
class InputDevice;
class View;
class ArtAssetLibrary;

#include <string>

//Basic Types
typedef unsigned int	Uint32;
typedef float			GAME_FLT;
typedef Uint32			GAME_INT;
typedef struct GAME_VEC
{
	GAME_FLT x;
	GAME_FLT y;
} GAME_VEC;

//========================================
//Base Game Constants
//========================================
const GAME_INT SCREEN_WIDTH = 800;
const GAME_INT SCREEN_HEIGHT = 600;
const GAME_INT GAME_FPS = 100;

//Event Types 
// (always start with GAME_NA and end with GAME_QUIT for looping reasons)
enum GAME_EVENT {
	GAME_NA,
	GAME_UP,
	GAME_DOWN, 
	GAME_LEFT, 
	GAME_RIGHT, 
	GAME_WEST,
	GAME_SOUTH,
	GAME_EAST,
	GAME_NORTH,
	GAME_MAP_TOGGLE, 
	GAME_QUIT
}; 

//Constants
const GAME_FLT PI = 3.14159f;
const GAME_INT MIN_OCTOROK_ANGLE = 0;
const GAME_INT MAX_OCTOROK_ANGLE = 5;
const GAME_INT MIN_OCTOROK_RADIUS = 1;
const GAME_INT MAX_OCTOROK_RADIUS = 3;
const GAME_FLT DEFAULT_LEEVER_SPEED = 2.0f;
const GAME_INT MIN_LEEVER_DISTANCE = 0;
const GAME_INT MAX_LEEVER_DISTANCE = 250;
const GAME_FLT VIEW_SPEED = 2.5f;

// Link Constants
const GAME_FLT LINK_SPEED = 2.0f;

// Mini Map Constants
const GAME_INT MINI_MAP_WIDTH = (int)(SCREEN_WIDTH / 5); // scale the map based off screen size
const GAME_INT MINI_MAP_HEIGHT = (int)(SCREEN_HEIGHT / 5); // make a square map
const GAME_INT MINI_MAP_OFFSET = 30; // pixels of padding/margin between the map sides and screen sides

// Object Factory Initializers for easy setting of parameters with components
struct GAME_OBJECTFACTORY_INITIALIZERS
{
	std::string textureId;
	std::string texturePath;
	GAME_VEC position;
	GAME_FLT angle;
	bool verticalSlide;
	bool radius;
	View* view;
	GraphicsDevice* gDevice;
	InputDevice* iDevice;
	ArtAssetLibrary* aLibrary;
};