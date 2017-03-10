#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include "GameObject.h"

class Component
{
public:
	Component(std::shared_ptr<GameObject> owner);
	~Component();
	void OwnerDestroyed();
	std::shared_ptr<GameObject> GetOwner();
	virtual void Start()=0;
	virtual void Update()=0;
	virtual void Finish()=0;

protected:
	std::shared_ptr<GameObject> _owner;
};


#endif