#include "RedLeever.h"
#include "Definitions.h"

#include <random>

RedLeever::RedLeever()
{
	// Setup the RNG (Random Number Generator)
	static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<GAME_INT> ud(MIN_LEEVER_DISTANCE, MAX_LEEVER_DISTANCE+1);

	movingLeft = false;
	speed = DEFAULT_LEEVER_SPEED;
	distance = ud(e);
	//angle = 0.0f;
}

RedLeever::~RedLeever()
{

}

//void RedLeever::Update()
//{
//	if (position.x >= (startPosition.x + distance))
//		movingLeft = true;
//
//	if (position.x <= (startPosition.x - distance))
//		movingLeft = false;
//
//	if (movingLeft)
//		position.x -= speed; 
//	else
//		position.x += speed;
//}
//
//void RedLeever::Draw(View* view)
//{
//	texture->Draw(renderer, view, position, 0.0f, NULL);
//}