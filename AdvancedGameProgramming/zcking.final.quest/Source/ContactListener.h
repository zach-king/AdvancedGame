#pragma once

#include "Box2D/Box2D.h"
#include "Game.h"

class Object;

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) { }

	void EndContact(b2Contact* contact) { }

	// Before solving for collision
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	// After solving for collision
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) { }

	void SetGame(Game*);

private:
	Game* game;
};