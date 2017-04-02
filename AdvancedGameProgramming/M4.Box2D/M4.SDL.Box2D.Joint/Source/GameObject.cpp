#include "GameFunctions.h"
#include "Texture.h"
#include "GameObject.h"

GameObject::GameObject()
{
	renderer = NULL;
	texture = NULL;

	body = NULL;

	command = "";

	initialized = false;
}

GameObject::~GameObject()
{
	//Unhook renderer from object
	renderer = NULL;
	texture->free();
	texture = NULL;
}

bool GameObject::Initialize(SDL_Renderer* renderer,std::string path, b2World* world, Uint32 x, Uint32 y)
{
	//Assign the renderer for  this object
	this->renderer = renderer;

	//Load the Art Asset
	texture = new Texture();
	texture->load(renderer,path);

	//Initialize the SDL_ttf

	//Load Font
	font = TTF_OpenFont( "./Assets/Fonts/impact.ttf", 48 );
	if( font == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	//
	//Initialize Physics
	//
	bd.type = b2_dynamicBody;
	bd.position.Set(RW2PW((int)x),RW2PW((int)y));
    bd.angle = RW2PWAngle(60.0f);
	body = world->CreateBody(&bd);  //Register Body with Physics World

	//Set up physics shape
    shape.m_radius = RW2PW(texture->getWidth()/1.5f);

	//Set up physics fixture (shape, density, restitution)
	shapefd.shape = &shape;
	shapefd.density = 0.1f;
	shapefd.friction = 0.5f;
	shapefd.restitution = 0.9f;
	body->CreateFixture(&shapefd); //Register fixture with physics world

	initialized = true;
	return(initialized);
}

void GameObject::HandleEvent(SDL_Event* event)
{
	switch(event->type)
	{
	case SDL_KEYDOWN:
		switch(event->key.keysym.sym)
		{
		case SDLK_LEFT:
			command = "left";
			break;
		case SDLK_RIGHT:

			command = "right";
			break;
		}
	}
}


void GameObject::Update(float dt)
{

	if(command == "left")
	{
		body->SetAngularVelocity(body->GetAngularVelocity()-2.0f*dt);
	}

	if(command == "right")
	{
		body->SetAngularVelocity(body->GetAngularVelocity()+2.0f*dt);
	}

}

void GameObject::Draw()
{

	//Convert Physics World Position to Render World Position
	b2Vec2 position = body->GetPosition();
	float drawX = PW2RW(position.x) - texture->getWidth()/2.0f;
	float drawY = PW2RW(position.y) - texture->getHeight()/2.0f;
    float32 angle = body->GetAngle();

	//Render to the Screen
	texture->renderEx(renderer,(int)drawX,(int)drawY,PW2RWAngle(angle),NULL);

	if(command != "")
	{

		//Render Command to Text
		SDL_Color textColor = { 255, 255, 51 };
		SDL_Texture* textSheetTexture = SDL_CreateTextureFromSurface( renderer,  TTF_RenderText_Solid(font, command.c_str(), textColor));

		//Set rendering space and render to screen
		int width=0,height=0;
		SDL_QueryTexture(textSheetTexture,NULL,NULL,&width,&height);
		SDL_Rect renderQuad = {(Uint32)PW2RW(position.x),(Uint32)PW2RW(position.y)-80, width, height};

		//Render to screen
		SDL_RenderCopy(renderer, textSheetTexture, NULL, &renderQuad );

		//Reset command
		command = "";
	}
}


b2Body* GameObject::getPhysicsBody()
{
    return(body);
}