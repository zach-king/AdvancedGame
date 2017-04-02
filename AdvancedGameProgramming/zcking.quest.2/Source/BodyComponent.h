#pragma once

#include "Component.h"
#include "Definitions.h"

#include <memory>


class BodyComponent : public Component
{
public:
	BodyComponent();
	BodyComponent(std::shared_ptr<Object> owner);
	~BodyComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::unique_ptr<Object> Update();
	bool Finish();

	GAME_VEC getPosition();
	void setPosition(GAME_VEC);
	GAME_FLT getAngle();
	void setAngle(GAME_FLT);

protected:
	GAME_VEC position;
	GAME_FLT angle;
};