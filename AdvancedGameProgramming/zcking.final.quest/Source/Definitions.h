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

// Link Constants
const GAME_FLT LINK_SPEED = 15.0f;
const GAME_INT ARROW_LIFETIME = 100; // measured in frames.
const GAME_INT ARROW_DAMAGE = 100;
const GAME_INT ARROW_SPEED = 30;
const GAME_INT COLLISION_DAMAGE = 30;
const GAME_INT FIRE_RATE = 90; // my own custom thing so can't machine gun the arrows (measured in frames)
const GAME_INT PLAYER_ZONE_HEIGHT = 200; // how much y-height the player can move in (vertically), from bottom of screen
const GAME_INT PLAYER_SIDE_PADDING = 0; // keeps the player's sprite from getting "over" the edge of the screen

// UI Constants
const GAME_INT UI_HEALTH_PADDING = 25;

// Score constants
const GAME_INT RED_PIRATE_SCORE = 100;
const GAME_INT BLACK_PIRATE_SCORE = 50;

// Object Factory Initializers for easy setting of parameters with components
struct GAME_OBJECTFACTORY_INITIALIZERS
{
	std::vector<std::string> textureIds;
	std::string texturePath;
	GAME_VEC position;
	GAME_FLT angle;
	GAME_FLT speed;
	Game* game;
	GAME_INT health;
	GAME_INT arrow_life;
	GAME_BODY_TYPE bodyType;
	GAME_OBJECT_SHAPE bodyShape;
	GAME_FLT bodyDensity;
	GAME_FLT bodyFriction;
	GAME_FLT bodyRestitution;
	GAME_FLT bodyAngDamping;
	GAME_FLT bodyLinDamping;
	bool bodyIsBullet;
	bool bodyRotates;
	std::string category;
};

// normal vector constants
const GAME_VEC VEC_LEFT = { -1.0f, 0.0f };
const GAME_VEC VEC_RIGHT = { 1.0f, 0.0f };
const GAME_VEC VEC_UP = { 0.0f, 1.0f };
const GAME_VEC VEC_DOWN = { 0.0f, -1.0f };
const GAME_VEC VEC_ZERO = { 0.0f, 0.0f };

// Asteroid constants
const GAME_FLT MIN_ASTEROID_SPIN_SPEED = 0.2f;
const GAME_FLT MAX_ASTEROID_SPIN_SPEED = 3.0f;

// Collision constants
const short CATEGORY_PLAYER	= 0x0001;
const short CATEGORY_ENEMY	= 0x0002;
const short CATEGORY_OBSTACLE = 0x0004;
const short CATEGORY_PLAYERBULLET = 0x0008;
const short CATEGORY_GAME		= 0x0010;

const short MASK_PLAYER = CATEGORY_ENEMY | CATEGORY_OBSTACLE | CATEGORY_GAME;
const short MASK_ENEMY = CATEGORY_PLAYER | CATEGORY_OBSTACLE | CATEGORY_ENEMY | CATEGORY_PLAYERBULLET;
const short MASK_OBSTACLE = CATEGORY_PLAYER | CATEGORY_OBSTACLE | CATEGORY_ENEMY | CATEGORY_PLAYERBULLET;
const short MASK_PLAYERBULLET = CATEGORY_ENEMY | CATEGORY_OBSTACLE;
const short MASK_GAME = CATEGORY_PLAYER;