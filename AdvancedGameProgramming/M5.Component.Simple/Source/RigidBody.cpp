#include"GameFunctions.h"
#include"RigidBody.h"

RigidBody::RigidBody(std::shared_ptr<GameObject> owner) : Component(owner){}

RigidBody::~RigidBody(){}

void RigidBody::Initialize(b2World* world)
{
	//Intialize Body Definition
	bd.type = b2_dynamicBody;
	bd.position.Set(RW2PW(200),RW2PW(200));
    bd.angle = RW2PWAngle(60.0f);

	//Create Body within Physics World
	body = world->CreateBody(&bd);  // Register Body with Physics World

	//Initialize Shape
	shape.SetAsBox(RW2PW(172.0f/2.0f),RW2PW(116.0f/2.0f)); //Requires half widths of texture size

	//Initialize Fixture Definition (shape, density, restitution)
	shapefd.shape = &shape;
	shapefd.density = 0.001f;
	shapefd.friction = 0.5f;
	shapefd.restitution = 0.9f;

	//Create Fixture within Body (links to Physics World)
	body->CreateFixture(&shapefd); //Register fixture with physics world
}

void RigidBody::Start(){}

void RigidBody::Update(){}

void RigidBody::Finish(){}


b2Vec2 RigidBody::GetPosition(){
	return(body->GetPosition());
}

float RigidBody::GetAngle()
{
	return(body->GetAngle());
}

b2Body* RigidBody::GetBody()
{
	return(body);
}