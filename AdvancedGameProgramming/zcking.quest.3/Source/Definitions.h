#pragma once

class Game;

#include <string>
#include <vector>

//Basic Types
typedef unsigned int	Uint32;
typedef float			GAME_FLT;
typedef Uint32			GAME_INT;
typedef struct GAME_VEC
{
	GAME_FLT x;
	GAME_FLT y;
} GAME_VEC;

const GAME_FLT GRAVITY_X = 0;
const GAME_FLT GRAVITY_Y = 0;

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
	GAME_FIRE,
	GAME_QUIT
}; 

// Physics enums
enum GAME_OBJECT_SHAPE {
	GAME_RECTANGLE,
	GAME_CIRCLE
};

enum GAME_BODY_TYPE {
	GAME_STATIC,		// doesn't move
	GAME_KINEMATIC,		// moves but not really going to be affected
	GAME_DYNAMIC		// interacts with other objects
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

// View Constants
const GAME_FLT VIEW_SPEED = 2.5f;
const GAME_FLT VIEW_PADDING_X = 150.0f; // how close to edge of screen can 
									  // player get before view moves
const GAME_FLT VIEW_PADDING_Y = 100.0f;

// Link Constants
const GAME_FLT LINK_SPEED = 2.0f;
const GAME_INT ARROW_LIFETIME = 50; // measured in frames.
const GAME_INT ARROW_SPEED = 3.0f;
const GAME_INT FIRE_RATE = 60; // my own custom thing so can't machine gun the arrows (measured in frames)

// Mini Map Constants
const GAME_INT MINI_MAP_WIDTH = (int)(SCREEN_WIDTH / 5); // scale the map based off screen size
const GAME_INT MINI_MAP_HEIGHT = (int)(SCREEN_HEIGHT / 5); // make a square map
const GAME_INT MINI_MAP_OFFSET = 30; // pixels of padding/margin between the map sides and screen sides

// Object Factory Initializers for easy setting of parameters with components
struct GAME_OBJECTFACTORY_INITIALIZERS
{
	std::vector<std::string> textureIds;
	std::string texturePath;
	GAME_VEC position;
	GAME_FLT angle;
	bool verticalSlide;
	bool radius;
	Game* game;
	GAME_INT arrow_life;
	GAME_BODY_TYPE bodyType;
	GAME_OBJECT_SHAPE bodyShape;
	GAME_FLT bodyDensity;
	GAME_FLT bodyFriction;
	GAME_FLT bodyRestitution;
	GAME_FLT bodyAngDamping;
	GAME_FLT bodyLinDamping;
};

const GAME_VEC VEC_LEFT = { -1.0f, 0.0f };
const GAME_VEC VEC_RIGHT = { 1.0f, 0.0f };
const GAME_VEC VEC_UP = { 0.0f, 1.0f };
const GAME_VEC VEC_DOWN = { 0.0f, -1.0f };
const GAME_VEC VEC_ZERO = { 0.0f, 0.0f };