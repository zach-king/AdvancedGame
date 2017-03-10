#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include"Component.h"
#include "Box2D/Box2D.h"


class RigidBody : public Component
{
public:

	RigidBody(std::shared_ptr<GameObject>);
	~RigidBody();
	void Initialize(b2World* world);

	void Start();
	void Update();
	void Finish();

	b2Vec2 GetPosition();
	float GetAngle();
	b2Body* GetBody();

protected:
	
	//Box2D Physics Components
    b2BodyDef bd;
    b2PolygonShape shape;
    b2FixtureDef shapefd;
    b2Body* body;
};


#endif