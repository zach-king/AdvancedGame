#include"GameFunctions.h"
#include"Behavior.h"
#include"RigidBody.h"

Behavior::Behavior(std::shared_ptr<GameObject> owner) : Component(owner){}

Behavior::~Behavior(){}

void Behavior::Initialize(float dt)
{
	this->dt = dt;
}

void Behavior::Start(){}

void Behavior::Update()
{
	float PI = 3.14159;
	float magnitude = 10.0f;

	//Convert Physics World Position to Render World Position
	std::shared_ptr<RigidBody> rigidBody = _owner->GetComponent<RigidBody>();
	b2Body* body = rigidBody->GetBody();

	if(body)
	{
		b2Vec2 force;
		force.x=magnitude*cos(body->GetAngle()-PI/2.0f);
		force.y=magnitude*sin(body->GetAngle()-PI/2.0f);
		body->ApplyForce(force,body->GetPosition());
	}
}

void Behavior::Finish(){}
