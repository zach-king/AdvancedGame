#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "GameFunctions.h"
#include "GraphicsDevice.h"
#include "Texture.h"

#include <memory>

SpriteComponent::SpriteComponent() : Component() {}

SpriteComponent::SpriteComponent(std::shared_ptr<Object> owner) : Component(owner)
{
	texture = NULL;
	gDevice = NULL;
}

SpriteComponent::~SpriteComponent() {}


bool SpriteComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	this->gDevice = initializers.gDevice;

	//Add Sprite to gDevice
	gDevice->AddSprite(this);

	//Load the Art Asset
	texture = new Texture();
	bool loaded = texture->load(gDevice->getRenderer(), initializers.texturePath);
	if (!loaded)
		return false;
	view = initializers.view;

	return true;
}

std::unique_ptr<Object> SpriteComponent::Update()
{
	return nullptr;
}

bool SpriteComponent::Finish()
{
	return false;
}

void SpriteComponent::Draw()
{
	//Convert Physics World Position to Render World Position
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();

	//Extract position and angle
	GAME_VEC position = body->getPosition();
	GAME_FLT angle = body->getAngle();

	//GAME_VEC drawPos;
	//drawPos.x = PW2RW(position.x) - texture->getWidth() / 2.0;
	//drawPos.y = PW2RW(position.y) - texture->getHeight() / 2.0;
	//float drawAngle = PW2RWAngle(angle);

	//Render to the Screen
	texture->Draw(gDevice->getRenderer(), view, position, angle, NULL);
}

Texture * SpriteComponent::getTexture()
{
	return texture;
}
