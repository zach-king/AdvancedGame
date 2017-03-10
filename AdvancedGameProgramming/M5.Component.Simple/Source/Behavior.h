#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include"Component.h"
class GameObject;
class GraphicsDevice;
class Texture;

class Behavior : public Component
{
public:
	Behavior(std::shared_ptr<GameObject>);
	~Behavior();
	void Initialize(float);

	void Start();
	void Update();
	void Finish();

protected:
	float dt;
};


#endif