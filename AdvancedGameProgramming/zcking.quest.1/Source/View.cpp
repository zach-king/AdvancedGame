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
	// Get event and behave accordingly
	GAME_EVENT event = iDevice->GetEvent();

	switch (event)
	{
	case GAME_NA:
		break;
	case GAME_UP:
		position.y += VIEW_SPEED;
		break;
	case GAME_DOWN:
		position.y -= VIEW_SPEED;
		break;
	case GAME_LEFT:
		position.x -= VIEW_SPEED;
		break;
	case GAME_RIGHT:
		position.x += VIEW_SPEED;
		break;
	case GAME_QUIT:
		return true;
	}

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