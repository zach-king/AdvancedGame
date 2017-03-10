#pragma once

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
enum GAME_EVENT {GAME_NA,GAME_UP,GAME_DOWN,GAME_LEFT,GAME_RIGHT, GAME_MAP_TOGGLE, GAME_QUIT};

//Constants
const GAME_FLT PI = 3.14159f;
const GAME_INT MIN_OCTOROK_ANGLE = 0;
const GAME_INT MAX_OCTOROK_ANGLE = 5;
const GAME_FLT DEFAULT_LEEVER_SPEED = 2.0f;
const GAME_INT MIN_LEEVER_DISTANCE = 0;
const GAME_INT MAX_LEEVER_DISTANCE = 250;
const GAME_FLT VIEW_SPEED = 2.5f;

// Mini Map Constants
const GAME_INT MINI_MAP_WIDTH = (int)(SCREEN_WIDTH / 5); // scale the map based off screen size
const GAME_INT MINI_MAP_HEIGHT = (int)(SCREEN_HEIGHT / 5); // make a square map
const GAME_INT MINI_MAP_OFFSET = 30; // pixels of padding/margin between the map sides and screen sides