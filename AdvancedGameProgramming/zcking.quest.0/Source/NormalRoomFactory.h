#ifndef NORMALROOMFACTORY_H
#define NORMALROOMFACTORY_H

#include "RoomFactory.h"

class NormalRoomFactory : public RoomFactory
{
public:
	virtual Room* create();
};

#endif