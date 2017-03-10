#pragma once

#include "Object.h"

// Blue Octorok class
class BlueOctorok : public Object
{
public:
	BlueOctorok();
	~BlueOctorok();
	void Update();
	void Draw(View*);
	
private:
	// Helper methods for rotations
	GAME_FLT degToRads(GAME_FLT);
	GAME_FLT radsToDegs(GAME_FLT);
};