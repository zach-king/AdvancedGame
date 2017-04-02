#include "BlueLeever.h"

#include <iostream>
#include <random>

BlueLeever::BlueLeever()
{
	// Setup the RNG (Random Number Generator)
	static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<GAME_INT> ud(MIN_LEEVER_DISTANCE, MAX_LEEVER_DISTANCE+1);

	movingUp = false;
	speed = DEFAULT_LEEVER_SPEED;
	distance = ud(e);
}

BlueLeever::~BlueLeever()
{

}