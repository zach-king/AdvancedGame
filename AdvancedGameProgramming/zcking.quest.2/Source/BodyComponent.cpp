#include "BodyComponent.h"
#include "GameFunctions.h"
#include "Object.h"
#include "SpriteComponent.h"
#include "Texture.h"

#include "SDL.h"

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
	view = initializers.view;

	return true;
}

std::unique_ptr<Object> BodyComponent::Update()
{
	return nullptr;
}

bool BodyComponent::Finish()
{
	return false;
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
