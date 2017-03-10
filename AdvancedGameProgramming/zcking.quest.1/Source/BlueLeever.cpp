#include "BlueLeever.h"

#include <iostream>
#include <random>

BlueLeever::BlueLeever()
{
	// Setup the RNG (Random Number Generator)
	static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<GAME_INT> ud(MIN_LEEVER_DISTANCE, MAX_LEEVER_DISTANCE+1);

	// Initialize the members
	movingUp = false;
	speed = DEFAULT_LEEVER_SPEED;
	distance = ud(e);
	angle = 0.0f;
}

BlueLeever::~BlueLeever()
{

}

void BlueLeever::Update()
{
	// Switch direction when needed
	if (position.y >= (startPosition.y + distance))
		movingUp = true;
	
	if (position.y <= (startPosition.y - distance))
		movingUp = false;

	// Based off direction, change position
	if (movingUp)
		position.y -= speed; // with graphics window, origin is in top-left so adding to y goes down and vice versa
	else
		position.y += speed;
}

void BlueLeever::Draw(View* view)
{
	texture->Draw(renderer, view, position, 0.0f, NULL);
}