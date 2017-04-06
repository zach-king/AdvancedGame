#include "BodyComponent.h"
#include "GameFunctions.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Game.h"

#include "SDL.h"

// Body Component pretty much just stores certain "Physics" attributes for the object it's attached to
// and those attribtues are used by other components

BodyComponent::BodyComponent() : Component() {}

BodyComponent::BodyComponent(std::shared_ptr<Object> owner) : Component(owner)
{
}

BodyComponent::~BodyComponent()
{
}

bool BodyComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	position = initializers.position;
	angle = initializers.angle;
	view = initializers.game->getView();

	return true;
}

std::unique_ptr<Object> BodyComponent::Update()
{
	return nullptr;
}

bool BodyComponent::Finish()
{
	this->view = NULL;
	return true;
}

GAME_VEC BodyComponent::getPosition()
{
	return position;
}

void BodyComponent::setPosition(GAME_VEC pos)
{
	position = pos;
}

float BodyComponent::getAngle()
{
	return angle;
}

void BodyComponent::setAngle(GAME_FLT ang)
{
	angle = ang;
}
