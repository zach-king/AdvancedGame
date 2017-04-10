#include "PlayerInputComponent.h"
#include "BodyComponent.h"
#include "GameFunctions.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "ProjectileComponent.h"
#include "SpriteComponent.h"

#include <memory>
#include <math.h>
#include <string>

PlayerInputComponent::PlayerInputComponent() : Component()
{
}

PlayerInputComponent::PlayerInputComponent(std::shared_ptr<Object> owner) : Component(owner)
{
}

PlayerInputComponent::~PlayerInputComponent()
{
}

bool PlayerInputComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	iDevice = initializers.game->getInputDevice();
	oFactory = initializers.game->getObjectFactory();
	pDevice = initializers.game->getPhysicsDevice();

	arrowInits = initializers;
	canFire = true;
	fireAngle = 180; // down (0 points up)

	return true;
}

std::unique_ptr<Object> PlayerInputComponent::Update()
{
	// Handle player reloading flag and timing
	if (!canFire)
	{
		reloadFrames++;
		if (reloadFrames > FIRE_RATE)
			canFire = true;
	}

	// Get the sprite and body components since they might be changed
	std::shared_ptr<SpriteComponent> sprite = _owner->GetComponent<SpriteComponent>();
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	GAME_VEC pos = body->getPosition();
	GAME_FLT ang = body->getAngle();

	// Left arrow key pressed?
	GAME_VEC velocity = VEC_ZERO;
	if (iDevice->GetEvent(GAME_LEFT))
	{
		// Ask for LinkLeft sprite texture change from SC
		if (sprite->getTextureId() != "LinkLeft")
			sprite->SetTexture("LinkLeft");

		// Adjust Position
		velocity = { -1 * LINK_SPEED, 0 };
		fireAngle = 270;
	}

	if (iDevice->GetEvent(GAME_RIGHT))
	{
		// Ask for LinkLeft sprite texture change from SC
		if (sprite->getTextureId() != "LinkRight")
			sprite->SetTexture("LinkRight");

		// Adjust Position
		velocity = { 1 * LINK_SPEED, 0 };
		fireAngle = 90;
	}

	if (iDevice->GetEvent(GAME_UP))
	{
		// Ask for LinkLeft sprite texture change from SC
		if (sprite->getTextureId() != "LinkUp")
			sprite->SetTexture("LinkUp");

		// Adjust Position
		velocity = { 0, -1 * LINK_SPEED };
		fireAngle = 0;
	}

	if (iDevice->GetEvent(GAME_DOWN))
	{
		// Ask for LinkLeft sprite texture change from SC
		if (sprite->getTextureId() != "LinkDown")
			sprite->SetTexture("LinkDown");

		// Adjust Position
		velocity = { 0, 1 * LINK_SPEED };
		fireAngle = 180;
	}

	pDevice->SetLinearVelocity(_owner.get(), velocity);

	// Old Movement Code (for regular assignment)
	/*if (iDevice->GetEvent(GAME_UP))
	{
		pos.x += LINK_SPEED * sinf(degToRads(ang));
		pos.y -= LINK_SPEED * cosf(degToRads(ang));
	}

	if (iDevice->GetEvent(GAME_DOWN))
	{
		pos.x -= LINK_SPEED * sinf(degToRads(ang));
		pos.y += LINK_SPEED * cosf(degToRads(ang));
	}*/

	body->setPosition(pos);
	//body->setAngle(ang);  // old; for regular movement

	// Did Link fire any arrows?
	if (iDevice->GetEvent(GAME_FIRE) && canFire)
	{
		// Initiate need for reload
		canFire = false;
		reloadFrames = 0;

		// Store names of arrow components
		std::vector<std::string> compNames;

		// Set the inits for the arrow components
		arrowInits.arrow_life = ARROW_LIFETIME;
		arrowInits.position = pos;
		arrowInits.angle = fireAngle;
		arrowInits.bodyType = GAME_DYNAMIC;
		arrowInits.bodyShape = GAME_RECTANGLE;
		arrowInits.bodyDensity = 0.5f;
		arrowInits.bodyFriction = 0.0f;
		arrowInits.bodyRestitution = 1.0f;
		arrowInits.bodyAngDamping = 0.0f;
		arrowInits.bodyLinDamping = 0.0f;
		arrowInits.bodyIsBullet = true;
		arrowInits.textureIds.push_back("Arrow");

		// Push the necessary component names (object factory will create and initialize)
		compNames.push_back("Sprite");
		compNames.push_back("Body");
		compNames.push_back("Projectile");

		// Create the object and add it to the game world
		std::shared_ptr<Object> arrow = oFactory->create(compNames, arrowInits);
		arrowInits.game->AddObject(arrow);
	}

	return nullptr;
}

bool PlayerInputComponent::Finish()
{
	this->iDevice = NULL;
	this->oFactory = NULL;

	return true;
}