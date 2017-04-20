#include "BodyComponent.h"
#include "GameFunctions.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Game.h"

#include "SDL.h"

BodyComponent::BodyComponent() : Component() 
{
}

BodyComponent::BodyComponent(std::shared_ptr<Object> owner) : Component(owner)
{
}

BodyComponent::~BodyComponent()
{
}

bool BodyComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	position = inits.position;
	angle = inits.angle;

	this->pDevice = inits.game->getPhysicsDevice();
	bool success = this->pDevice->CreateFixture(
		_owner,
		position,
		angle,
		inits.bodyType,
		inits.bodyShape,
		inits.bodyDensity,
		inits.bodyFriction,
		inits.bodyRestitution,
		inits.bodyAngDamping,
		inits.bodyLinDamping,
		inits.bodyIsBullet,
		inits.bodyRotates,
		inits.category
		);


	return true;
}

void BodyComponent::Update()
{
}

bool BodyComponent::Finish()
{
	pDevice->RemoveObject(_owner.get());
	return true;
}

GAME_VEC BodyComponent::getPosition()
{
	return pDevice->GetPosition(_owner.get());
}

void BodyComponent::setPosition(GAME_VEC pos)
{
	pDevice->SetTransform(_owner.get(), pos, pDevice->GetAngle(_owner.get()));
}

float BodyComponent::getAngle()
{
	return pDevice->GetAngle(_owner.get());
}

void BodyComponent::setAngle(GAME_FLT ang)
{
	pDevice->SetAngle(_owner.get(), ang);
}
