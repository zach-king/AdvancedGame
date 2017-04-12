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
	Object* target;
	Object* arrow;

	std::string aName = objectA->getName();
	std::string bName = objectB->getName();


	if (aName == "Arrow")
	{
		arrow = objectA;
		target = objectB;
	}
	else if (bName == "Arrow")
	{
		arrow = objectB;
		target = objectA;
	}
	else
	{
		return; // if no arrow involved, we don't care
	}

	std::string targetName = target->getName();

	// Apply damage to the target object (leever or octorok)
	if (targetName.find("Leever") != std::string::npos ||
		targetName.find("Octorok") != std::string::npos)
	{
		target->GetComponent<HealthComponent>()->TakeDamage(ARROW_DAMAGE);

		// Destroy the arrow
		arrow->setIsDead(true);
	}
}