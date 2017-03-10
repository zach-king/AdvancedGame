#include "RedOctorok.h"

#include <random>
#include <math.h>

GAME_FLT RedOctorok::degToRads(GAME_FLT degs)
{
	return degs * (PI / 180.0f);
}

GAME_FLT RedOctorok::radsToDegs(GAME_FLT rads)
{
	return rads * (180.0f / PI);
}

RedOctorok::RedOctorok()
{
}

RedOctorok::~RedOctorok()
{

}

void RedOctorok::Update()
{
	// Setup the RNG (Random Number Generator)
	static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<GAME_INT> ud(MIN_OCTOROK_ANGLE, MAX_OCTOROK_ANGLE+1);

	// Continue to decrement the angle by a random amount
	angle -= degToRads((GAME_FLT)(ud(e)));

	// Move the octorok (not just spin)
	position.x += cosf(angle); // cos for x component
	position.y += sinf(angle); // sin for y component
}

void RedOctorok::Draw(View* view)
{
	texture->Draw(renderer, view, position, 90.0f + radsToDegs(angle), NULL);
}

