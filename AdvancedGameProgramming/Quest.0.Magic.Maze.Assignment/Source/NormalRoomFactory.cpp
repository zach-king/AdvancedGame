#include "NormalRoomFactory.h"
#include "NormalRoom.h"

Room* NormalRoomFactory::create()
{
	return ((Room *)(new NormalRoom()));
}