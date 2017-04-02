#pragma once

#include "Object.h"

class RedOctorok : public Object
{
public:
	RedOctorok();
	~RedOctorok();
	//void Update();
	//void Draw(View*);

private:
	GAME_FLT degToRads(GAME_FLT);
	GAME_FLT radsToDegs(GAME_FLT);
};