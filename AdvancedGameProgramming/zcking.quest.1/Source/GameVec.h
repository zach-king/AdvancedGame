#pragma once

#include "Definitions.h"

class GameVec
{
public:
	GameVec();
	GameVec(GAME_FLT, GAME_FLT);
	~GameVec();

	GAME_FLT getMagnitude();

	friend GameVec operator+(const GameVec &vec1, const GameVec &vec2);

private:
	GAME_FLT x;
	GAME_FLT y;
};