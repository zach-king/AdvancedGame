#include "GameVec.h"

#include <math.h>

GameVec::GameVec()
{
	x = 0.0f;
	y = 0.0f;
}

GameVec::GameVec(GAME_FLT x, GAME_FLT y)
{
	this->x = x;
	this->y = y;
}

GAME_FLT GameVec::getMagnitude()
{
	return sqrtf(x*x + y*y);
}

GameVec operator+(const GameVec &vec1, const GameVec &vec2)
{
	return GameVec(vec1.x + vec2.x, vec1.y + vec2.y);
}