#include "GameFunctions.h"
#include "GraphicsDevice.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "Sprite.h"
#include "Behavior.h"

GameObject::GameObject()
{
	initialized = false;
}

GameObject::~GameObject()
{

	//for(auto comp: components)
	//{
	//	comp->OwnerDestroyed();
	//}
	//components.clear();

}

bool GameObject::Initialize(GraphicsDevice* gDevice,std::string path, b2World* world, float dt)
{

	//Create Components
	std::shared_ptr<RigidBody> body = std::make_shared<RigidBody>(shared_from_this());
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(shared_from_this());
	std::shared_ptr<Behavior> behavior = std::make_shared<Behavior>(shared_from_this());
	
	//Initialize Components
	body->Initialize(world);
	sprite->Initialize(gDevice,path);
	behavior->Initialize(dt);

	//Add Components to body
	AddComponent(body);
	AddComponent(sprite);
	AddComponent(behavior);

	//Call the start method
	if(!initialized)
	{
		for(auto comp : components)
		{
			comp->Start();
		}
		initialized = true;
	}

	return(initialized);
}

void GameObject::Update()
{
	for(auto comp : components)
	{
		comp->Update();
	}
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);
}