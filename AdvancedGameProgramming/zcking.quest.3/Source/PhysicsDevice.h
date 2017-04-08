#pragma once

#include "Box2D/Box2D.h"
#include "Definitions.h"
#include "Object.h"

#include <memory>

class PhysicsDevice
{
public:
	PhysicsDevice();
	PhysicsDevice(GAME_VEC);
	~PhysicsDevice();
	
	bool Initialize();
	bool Update(float dt); // dt = delta time
	bool CreateFixture(
		std::shared_ptr<Object> object,
		GAME_VEC position,
		GAME_FLT angle,
		GAME_BODY_TYPE bodyType,
		GAME_OBJECT_SHAPE objectShape,
		GAME_FLT density,
		GAME_FLT friction,
		GAME_FLT restitution,		// how bouncy
		GAME_FLT angularDamping,	// with spin, how quick to slow down
		GAME_FLT linearDamping		// same as angular, but with linear movement
		);

	bool CreateEdge(GAME_VEC, GAME_VEC);

	bool SetTransform(Object* object, GAME_VEC position, GAME_FLT angle);
	bool SetLinearVelocity(Object* object, GAME_VEC linearVelocity);
	bool SetAngularVelocity(Object* object, GAME_FLT angularVelocity);
	bool SetTorque(Object* object, GAME_FLT torque);
	bool SetLinearImpulse(Object* object, GAME_VEC forceVec, GAME_VEC forceCenter);
	bool SetStatic(Object* object);
	bool SetStopPhysics(Object* object);
	bool SetAngle(Object* object, GAME_FLT angle);

	GAME_FLT GetAngularVelocity(Object *object);
	GAME_VEC GetPosition(Object *object);
	GAME_FLT GetAngle(Object* object);
	GAME_VEC GetVelocity(Object* object);
	GAME_VEC GetLinearVelocity(Object* object);
	b2World* getWorld();

private:
	std::shared_ptr<b2World> world;
	const b2Vec2 gravity;

	b2Body* findBody(Object* object);
};