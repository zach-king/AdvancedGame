#pragma once

#include "Definitions.h"

#include <memory>

class Object;
class Game;
class InputDevice;

class View
{
public:
	View();
	~View();
	bool Initialize(InputDevice*, GAME_FLT, GAME_FLT);
	bool Update(GAME_FLT);
	GAME_VEC getPosition();
	GAME_FLT getAngle();
	GAME_VEC getCenter();
	void FindPlayer(Game*); // finds player with Game class and stores pointer (only needs calling once)

private:
	InputDevice* iDevice;
	GAME_VEC position;
	GAME_VEC center;
	GAME_FLT angle;

	// Pointer to player for border detection
	Object* player;
};