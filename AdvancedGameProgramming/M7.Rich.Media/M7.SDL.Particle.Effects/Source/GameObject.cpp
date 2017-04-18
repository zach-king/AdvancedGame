#include "GameObject.h"
#include "Texture.h"

GameObject::GameObject()
{
	renderer = NULL;
	texture = NULL;

}

GameObject::~GameObject()
{
	//Unhook renderer from object
	renderer = NULL;
	texture->free();
}
	
bool GameObject::Initialize(SDL_Renderer* renderer,std::string path, float x, float y, float vx, float vy, int da)
{
	//Assign the renderer for  this object
	this->renderer = renderer;

	//Load the Art Asset
	texture = new Texture();
	texture->load(renderer,path);

	xPosition = x;
	yPosition = y;

    xVelocity = vx;
    yVelocity = vy;

    alpha = 255;
    dAlpha = da;
    dead = false;

	return(true);
}


void GameObject::Update()
{
	//Update logic here
	xPosition += xVelocity;
	yPosition += yVelocity; 

	//Decrement alpha value;
	alpha-=dAlpha;

	//Set to dead if transparent
	if(alpha<0){
		dead=true;
	}
}

void GameObject::Draw()
{
	texture->renderEx(renderer,(int)xPosition,(int)yPosition,0,NULL,alpha);
}

bool GameObject::isDead()
{
    return(dead);
}