#include "BlueOctorok.h"

#include <random>
#include <math.h>

GAME_FLT BlueOctorok::degToRads(GAME_FLT degs)
{
	return degs * (PI / 180.0f);
}

GAME_FLT BlueOctorok::radsToDegs(GAME_FLT rads)
{
	return rads * (180.0f / PI);
}

BlueOctorok::BlueOctorok()
{

}

BlueOctorok::~BlueOctorok()
{

}

void BlueOctorok::Update()
{
	// Setup the RNG (Random Number Generator)
	static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<GAME_INT> ud(MIN_OCTOROK_ANGLE, MAX_OCTOROK_ANGLE+1);

	angle -= degToRads((GAME_FLT)(ud(e)));
}

void BlueOctorok::Draw(View* view)
{
	texture->Draw(renderer, view, position, 90.0f + radsToDegs(angle), NULL);
}