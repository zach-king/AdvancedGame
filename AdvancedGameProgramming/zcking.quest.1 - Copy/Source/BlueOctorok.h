#pragma once

#include "Object.h"

class BlueOctorok : public Object
{
public:
	BlueOctorok();
	~BlueOctorok();
	void Update();
	void Draw(View*);
	
private:
	GAME_FLT degToRads(GAME_FLT);
	GAME_FLT radsToDegs(GAME_FLT);
};