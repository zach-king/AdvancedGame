#pragma once

#include "Object.h"

class BlueOctorok : public Object
{
public:
	BlueOctorok();
	~BlueOctorok();
	
private:
	GAME_FLT degToRads(GAME_FLT);
	GAME_FLT radsToDegs(GAME_FLT);
};