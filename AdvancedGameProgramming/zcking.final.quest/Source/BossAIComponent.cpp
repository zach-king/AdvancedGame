#include "BossAIComponent.h"
#include "BodyComponent.h"

#include <random>

BossAIComponent::BossAIComponent() : Component() {}

BossAIComponent::BossAIComponent(std::shared_ptr<Object> owner) : Component(owner) {}

BossAIComponent::~BossAIComponent() {}

bool BossAIComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	game = inits.game;
	canFire = true;
	reloadFrames = 0;
	return true;
}

void BossAIComponent::Update()
{
	// Setup the RNG (Random Number Generator)
	/*static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<GAME_INT> ud(MIN_STRAFE_DISTANCE, MAX_STRAFE_DISTANCE + 1);*/

	// Handle reloading flag and timing
	if (!canFire)
	{
		reloadFrames++;
		if (reloadFrames > FIRE_RATE)
			canFire = true;
	}
	else
	{
		Shoot({ 0, BOSS_YMOD });
		Shoot({ BOSS_XMOD, BOSS_YMOD });
	}
}

bool BossAIComponent::Finish()
{
	game->AddScore(BOSS_SCORE);
	game->setProgress(true);
	return true;
}

void BossAIComponent::Shoot(GAME_VEC posMod)
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
	inits.position.x += posMod.x;
	inits.position.y += posMod.y;

	inits.angle = 90.0f;
	inits.force = VEC_UP;
	inits.speed = BOSS_BULLET_SPEED;
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