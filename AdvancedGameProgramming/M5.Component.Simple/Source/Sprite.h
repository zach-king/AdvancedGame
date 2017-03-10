#ifndef SPRITE_H
#define SPRITE_H

#include"Component.h"
class GameObject;
class GraphicsDevice;
class Texture;

class Sprite : public Component
{
public:
	Sprite(std::shared_ptr<GameObject>);
	~Sprite();
	void Initialize(GraphicsDevice*, std::string);

	void Start();
	void Update();
	void Finish();

	void Draw();
	void Present();

protected:
	Texture* texture;
	GraphicsDevice* gDevice;
};


#endif