
#include "Object.h"
#include "Texture.h"

#include <memory>

Object::Object()
{
	renderer = NULL;
	texture = NULL;
	startPosition.x = 0.0f;
	startPosition.y = 0.0f;
	position = startPosition;
	angle = 0.0f;
}

Object::~Object()
{
	renderer = NULL;
	texture->free();
}

bool Object::Initialize(SDL_Renderer* renderer, std::string path)
{
	if (renderer == NULL)
		return false;

	this->renderer = renderer;

	texture = std::make_unique<Texture>();
	startPosition.x = 0.0f;
	startPosition.y = 0.0f;
	position = startPosition;
	angle = 0.0f;

	return (texture->load(renderer, path));
}

void Object::setStartPosition(GAME_VEC vec)
{
	startPosition = vec;
}

void Object::setPosition(GAME_VEC vec)
{
	position = vec;
}

void Object::setAngle(GAME_FLT ang)
{
	angle = ang;
}