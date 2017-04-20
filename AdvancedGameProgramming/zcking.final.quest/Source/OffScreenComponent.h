#pragma once

#include "Component.h"
#include "BodyComponent.h"

class OffScreenComponent : public Component
{
public:
	OffScreenComponent();
	OffScreenComponent(std::shared_ptr<Object> owner);
	~OffScreenComponent();

	virtual bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	virtual void Update();
	virtual bool Finish();

protected:
	// Method to be overriden. Gets called when object goes off screen
	virtual void Trigger()=0;

	// Used for determing if object is off screen
	std::shared_ptr<BodyComponent> body;
};