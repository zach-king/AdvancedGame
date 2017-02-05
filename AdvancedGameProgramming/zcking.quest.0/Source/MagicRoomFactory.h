#ifndef MAGICROOMFACTORY_H
#define MAGICROOMFACTORY_H

#include "RoomFactory.h"

class MagicRoomFactory : public RoomFactory
{
public:
	virtual Room* create();
};

#endif