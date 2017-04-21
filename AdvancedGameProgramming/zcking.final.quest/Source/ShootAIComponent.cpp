#include "ShootAIComponent.h"
#include "BodyComponent.h"
#include "Object.h"

ShootAIComponent::ShootAIComponent() : Component() {}

ShootAIComponent::ShootAIComponent(std::shared_ptr<Object> owner) : Component(owner) {}

ShootAIComponent::~ShootAIComponent() {}

bool ShootAIComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	canFire = true;
	game = inits.game;
	return true;
}

void ShootAIComponent::Update()
{
	// Handle player reloading flag and timing
	if (!canFire)
	{
		reloadFrames++;
		if (reloadFrames > FIRE_RATE)
			canFire = true;
	}
	else
	{
		Shoot();
	}
}

bool ShootAIComponent::Finish()
{
	return true;
}

void ShootAIComponent::Shoot()
{
	// Initiate need for reload
	canFire = false;
	reloadFrames = 0;

	GAME_OBJECTFACTORY_INITIALIZERS inits;

	// Store names of arrow components
	std::vector<std::string> compNames;

	// Set the inits for the arrow components
	inits.arrow_life = ARROW_LIFETIME;
	inits.position = _owner->GetComponent<BodyComponent>()->getPosition();
	inits.angle = 270.0f;
	inits.force = VEC_UP;
	inits.speed = ENEMY_BULLET_SPEED;
	inits.game = game;

	// Load other physics stuff from library
	game->getAssetLibrary()->SearchPhysics("Enemy Bullet", &inits);

	inits.textureIds.push_back("Plasma Bullet");

	// Push the necessary component names (object factory will create and initialize)
	compNames.push_back("Sprite");
	compNames.push_back("Body");
	compNames.push_back("Projectile");
	compNames.push_back("DestroyOffScreen");

	// Create the object and add it to the game world
	std::shared_ptr<Object> arrow = game->getObjectFactory()->create(compNames, inits);
	arrow->setName("Enemy Bullet");
	inits.game->AddObject(arrow);

	// Play the player shoot sound
	game->getAudioDevice()->PlayClip("EnemyShoot");
}