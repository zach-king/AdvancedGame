#pragma once

#include "Object.h"

class RedLeever : public Object
{
public:
	RedLeever();
	~RedLeever();
	/*void Update();
	void Draw(View*);*/

private:
	bool movingLeft; // boolean flag for direction the leever is moving (left or right)
	GAME_FLT speed;  // adjustable speed for the leever's movement
	GAME_FLT distance; // distance the leever goes before turning around
};