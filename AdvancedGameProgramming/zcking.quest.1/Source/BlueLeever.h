#pragma once

#include "Object.h"

// Blue Leever Class
class BlueLeever : public Object
{
public:
	BlueLeever();
	~BlueLeever();
	void Update();
	void Draw(View*);

private:
	bool movingUp; // bool flag for which direction leever is moving (up or down)
	GAME_FLT speed;  // adjustable speed for the leever's movement
	GAME_FLT distance; // distance the leever goes before turning around
};