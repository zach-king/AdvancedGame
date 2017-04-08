#include "PhysicsDevice.h"
#include "GameFunctions.h"
#include "SpriteComponent.h"

PhysicsDevice::PhysicsDevice()
{
}

PhysicsDevice::PhysicsDevice(GAME_VEC gravity):gravity(RW2PW(gravity.x), RW2PW(gravity.y))
{
}

PhysicsDevice::~PhysicsDevice()
{
}

bool PhysicsDevice::Initialize()
{
	world = std::make_shared<b2World>(gravity);
	if (world == nullptr)
		return false;

	return true;
}

bool PhysicsDevice::Update(float dt)
{
	world->Step(dt, 8, 3);
	return true;
}

bool PhysicsDevice::CreateFixture(
	std::shared_ptr<Object> object, 
	GAME_VEC position,
	GAME_FLT angle, 
	GAME_BODY_TYPE bodyType, 
	GAME_OBJECT_SHAPE objectShape, 
	GAME_FLT density, GAME_FLT friction, 
	GAME_FLT restitution, GAME_FLT angularDamping, 
	GAME_FLT linearDamping)
{
	// Make a body definition
	std::unique_ptr<b2BodyDef> bd(std::make_unique<b2BodyDef>());

	// Make shapes
	b2PolygonShape pShape;
	b2CircleShape cShape;

	bd->userData = object.get();

	//bd->bullet = true; // tell box2d to do faster calculations for fast objects
		// for future stuff if needed

	// Set body type
	switch (bodyType)
	{
	case GAME_STATIC:
		bd->type = b2_staticBody;
		break;
	case GAME_KINEMATIC:
		bd->type = b2_kinematicBody;
		break;
	case GAME_DYNAMIC:
		bd->type = b2_dynamicBody;
		break;
	}

	// Set position and angle
	bd->position.Set(RW2PW(position.x), RW2PW(position.y));
	bd->angle = RW2PWAngle(angle);

	// Make the body in the world and set damping
	b2Body* body = world->CreateBody(bd.release());
	body->SetAngularDamping(angularDamping);
	body->SetLinearDamping(linearDamping);

	// Create fixture definition
	b2FixtureDef shapefd;

	// Create shape based off texture dimensions
	auto tex = object->GetComponent<SpriteComponent>()->getTexture();
	switch (objectShape)
	{
	case GAME_RECTANGLE:
		pShape.SetAsBox(
			RW2PW(tex->getWidth() / 2.0f),
			RW2PW(tex->getHeight() / 2.0f)
		);
		shapefd.shape = &pShape;
		break;
	case GAME_CIRCLE:
		cShape.m_radius = RW2PW(tex->getWidth() / 2.0f);
		shapefd.shape = &cShape;
		break;
	}

	// Set last attributes for shape
	shapefd.density = density;
	shapefd.friction = friction;
	shapefd.restitution = restitution;

	// Create and add the fixture from the shape to the body
	body->CreateFixture(&shapefd);

	return true;
}

bool PhysicsDevice::CreateEdge(GAME_VEC start, GAME_VEC finish)
{
	// Create body definition
	b2BodyDef bd;
	b2Body* edge = world->CreateBody(&bd);
	b2EdgeShape shape;
	
	// Set the shape/geometry
	shape.Set(GV2PV(start), GV2PV(finish));

	// Create fixture
	edge->CreateFixture(&shape, 0);
	return true;
}

b2Body* PhysicsDevice::findBody(Object* object)
{
	for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
	{
		if (object == body->GetUserData())
			return body;
	}

	return NULL;
}

bool PhysicsDevice::SetTransform(Object * object, GAME_VEC position, GAME_FLT angle)
{
	b2Body* body = findBody(object);
	if (body == NULL)
		return false;

	body->SetTransform(
		GV2PV(position),
		RW2PWAngle(angle)
	);

	return true;
}

bool PhysicsDevice::SetLinearVelocity(Object* object, GAME_VEC linearVelocity)
{
	b2Body* body = findBody(object);
	if (body == NULL)
		return false;

	body->SetLinearVelocity(GV2PV(linearVelocity));
	return true;
}

bool PhysicsDevice::SetAngularVelocity(Object* object, GAME_FLT angularVelocity)
{
	b2Body* body = findBody(object);
	if (body == NULL)
		return false;

	body->SetAngularVelocity(RW2PW(angularVelocity));
	return true;
}

bool PhysicsDevice::SetTorque(Object* object, GAME_FLT torque)
{
	b2Body* body = findBody(object);
	if (body == NULL)
		return false;

	body->ApplyTorque(RW2PW(torque), true);
	return true;
}

bool PhysicsDevice::SetLinearImpulse(Object* object, GAME_VEC forceVec, GAME_VEC forceCenter)
{
	b2Body* body = findBody(object);
	if (body == NULL)
		return false;

	body->ApplyLinearImpulse(
		GV2PV(forceVec),
		body->GetWorldPoint(GV2PV(forceCenter)),
		true
	);
	return true;
}

bool PhysicsDevice::SetStatic(Object* object)
{
	b2Body* body = findBody(object);
	if (body == NULL)
		return false;

	body->SetType(b2_staticBody);
	return true;
}

bool PhysicsDevice::SetStopPhysics(Object* object)
{
	b2Body* body = findBody(object);
	if (body == NULL)
		return false;

	body->SetActive(false);
	return true;
}

bool PhysicsDevice::SetAngle(Object* object, GAME_FLT angle)
{
	b2Body* body = findBody(object);
	if (body == NULL)
		return false;

	body->SetTransform(body->GetPosition(), RW2PWAngle(angle));
	return true;
}

GAME_FLT PhysicsDevice::GetAngularVelocity(Object *object)
{
	b2Body* body = findBody(object);
	return (PW2RW(body->GetAngularVelocity()));
}

GAME_VEC PhysicsDevice::GetPosition(Object *object)
{
	b2Body* body = findBody(object);
	return PV2GV(body->GetPosition());
}

GAME_FLT PhysicsDevice::GetAngle(Object* object)
{
	b2Body* body = findBody(object);
	return PW2RWAngle(body->GetAngle());
}

GAME_VEC PhysicsDevice::GetVelocity(Object* object)
{
	b2Body* body = findBody(object);
	return PV2GV(body->GetLinearVelocity());
}

GAME_VEC PhysicsDevice::GetLinearVelocity(Object* object)
{
	b2Body* body = findBody(object);
	return PV2GV(body->GetLinearVelocity());
}

b2World* PhysicsDevice::getWorld()
{
	return world.get();
}