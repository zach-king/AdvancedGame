#include "GameFunctions.h"
#include "GraphicsDevice.h"
#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "RigidBody.h"
#include "Texture.h"

Sprite::Sprite(std::shared_ptr<GameObject> owner) : Component(owner)
{
	texture = NULL;
	gDevice = NULL;
}

Sprite::~Sprite(){}

void Sprite::Initialize(GraphicsDevice* gDevice, std::string path)
{
	this->gDevice = gDevice;

	//Add Sprite to gDevice
	gDevice->AddSprite(this);

	//Load the Art Asset
	texture = new Texture();
	texture->load(gDevice->GetRenderer(),path);
}

void Sprite::Start(){}

void Sprite::Update(){}

void Sprite::Finish(){}

void Sprite::Draw()
{
	//Convert Physics World Position to Render World Position
	std::shared_ptr<RigidBody> body = _owner->GetComponent<RigidBody>();

	//Extract position and angle
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
	float drawX = PW2RW(position.x) - 172.0/2.0;
	float drawY = PW2RW(position.y) - 116.0/2.0;
	float drawAngle = PW2RWAngle(angle);

	//Render to the Screen
	texture->renderEx(gDevice->GetRenderer(),(int)drawX,(int)drawY,drawAngle,NULL);

}