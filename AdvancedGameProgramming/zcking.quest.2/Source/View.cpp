#include "View.h"
#include "Definitions.h"

#include <iostream>
#include <math.h>

View::View()
{
	iDevice = NULL;
	position.x = 0;
	position.y = 0;
	center.x = 0;
	center.y = 0;
	angle = 0.0f;
}

View::~View()
{

}

bool View::Initialize(InputDevice* input, GAME_FLT xPos, GAME_FLT yPos)
{
	if (input == NULL)
		return false;

	if (xPos < 0 || yPos < 0)
		return false;

	iDevice = input;
	angle = 90.0f;
	position.x = xPos;
	position.y = yPos;
	center.x = 0.0f;
	center.y = 1.0f;

	return true;
}

bool View::Update(GAME_FLT change)
{
	//printf("%f, %f\n", position.x, position.y); // debug

	// Get event and behave accordingly
	if (iDevice->GetEvent(GAME_NORTH))
		position.y += VIEW_SPEED;

	if (iDevice->GetEvent(GAME_SOUTH))
		position.y -= VIEW_SPEED;

	if (iDevice->GetEvent(GAME_EAST))
		position.x += VIEW_SPEED;

	if (iDevice->GetEvent(GAME_WEST))
		position.x -= VIEW_SPEED;

	if (iDevice->GetEvent(GAME_QUIT))
		return true;
	//std::cout << position.x;
	return false;
}

GAME_VEC View::getPosition()
{
	return position;
}

GAME_FLT View::getAngle()
{
	return angle;
}

GAME_VEC View::getCenter()
{
	return center;
}