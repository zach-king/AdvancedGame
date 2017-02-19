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

	angle -= degToRads((GAME_FLT)(ud(e)));

	position.x += cosf(angle);
	position.y += sinf(angle);
}

void RedOctorok::Draw(View* view)
{
	texture->Draw(renderer, view, position, 90.0f + radsToDegs(angle), NULL);
}

