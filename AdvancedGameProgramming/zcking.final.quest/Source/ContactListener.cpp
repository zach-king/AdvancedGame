#include "ContactListener.h"
#include "Object.h"
#include "Definitions.h"
#include "HealthComponent.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	// Get the two bodies that collided
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	// Get the two objects
	Object* objectA = static_cast<Object*>(bodyA->GetUserData());
	Object* objectB = static_cast<Object*>(bodyB->GetUserData());

	// If either object is NULL, it must be an Edge, so nothing should be done other than collide
	if (objectA == NULL || objectB == NULL)
		return;

	Object* target;
	Object* bullet;

	std::string aName = objectA->getName();
	std::string bName = objectB->getName();

	// Check if player collided with anything
	if (aName == "Player" || bName == "Player")
	{

		if (aName == "Player")
		{
			// Check if player hit an object that would take health from player
			if (bName.find("Pirate") != std::string::npos ||
				bName.find("Asteroid") != std::string::npos)
			{
				// Player takes damage
				objectA->GetComponent<HealthComponent>()->TakeDamage(COLLISION_DAMAGE);

				// Object get's destroyed
				objectB->setIsDead(true);
			}
			else if (bName == "Win")
			{
				// Player hit the win object, so win the game
				game->setWon(true);
			}
			else if (bName == "Enemy Bullet")
			{
				// Player takes damage
				objectA->GetComponent<HealthComponent>()->TakeDamage(ENEMY_BULLET_DAMAGE);

				// Object get's destroyed
				objectB->setIsDead(true);
			}
		}
		else
		{
			// Check if player hit an object that would take health from player
			if (aName.find("Pirate") != std::string::npos ||
				aName.find("Asteroid") != std::string::npos)
			{
				// Player takes damage
				objectB->GetComponent<HealthComponent>()->TakeDamage(COLLISION_DAMAGE);

				// Object get's destroyed
				objectA->setIsDead(true);
			}
			else if (aName == "Win")
			{
				// Player hit the win object, so win the game
				game->setWon(true);
			}
			else if (aName == "Enemy Bullet")
			{
				// Player takes damage
				objectB->GetComponent<HealthComponent>()->TakeDamage(ENEMY_BULLET_DAMAGE);

				// Object get's destroyed
				objectA->setIsDead(true);
			}
		}
		return;
	}
	else if (aName == "Plasma Bullet" || bName == "Plasma Bullet")
	{
		if (aName == "Plasma Bullet")
		{
			bullet = objectA;
			target = objectB;
		}
		else
		{
			bullet = objectB;
			target = objectA;
		}

		std::string targetName = target->getName();

		// Apply damage to the target object (leever or octorok)
		if (targetName.find("Pirate") != std::string::npos ||
			targetName.find("Asteroid") != std::string::npos ||
			targetName.find("Boss") != std::string::npos)
		{
			target->GetComponent<HealthComponent>()->TakeDamage(ARROW_DAMAGE);
		}

		// Destroy the bullet
		bullet->setIsDead(true);
	}
}

void ContactListener::SetGame(Game* g)
{
	game = g;
}