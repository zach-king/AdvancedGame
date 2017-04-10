#include "View.h"
#include "Definitions.h"
#include "InputDevice.h"
#include "Game.h"
#include "BodyComponent.h"
#include "Object.h"

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
	
	// Check player position and move based off our view padding
	std::shared_ptr<BodyComponent> playerBody = player->GetComponent<BodyComponent>();
	GAME_VEC playerPos = playerBody->getPosition();

	if (playerPos.x >= (position.x + SCREEN_WIDTH - VIEW_PADDING_X))
		position.x += VIEW_SPEED;

	if (playerPos.x <= position.x + VIEW_PADDING_X)
		position.x -= VIEW_SPEED;

	if (playerPos.y <= position.y + VIEW_PADDING_Y)
		position.y -= VIEW_SPEED;

	if (playerPos.y >= position.y + SCREEN_HEIGHT - VIEW_PADDING_Y)
		position.y += VIEW_SPEED;


	// Get event and behave accordingly
	if (iDevice->GetEvent(GAME_NORTH))
		position.y -= VIEW_SPEED;

	if (iDevice->GetEvent(GAME_SOUTH))
		position.y += VIEW_SPEED;

	if (iDevice->GetEvent(GAME_EAST))
		position.x += VIEW_SPEED;

	if (iDevice->GetEvent(GAME_WEST))
		position.x -= VIEW_SPEED;

	if (iDevice->GetEvent(GAME_QUIT))
		return true;

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

// Easily find the player after initializations have taken place
void View::FindPlayer(Game* game)
{
	player = game->GetObject("Link");
}