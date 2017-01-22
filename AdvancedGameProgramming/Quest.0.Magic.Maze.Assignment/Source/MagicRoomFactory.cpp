#include "MagicRoomFactory.h"
#include "MagicRoom.h"

Room* MagicRoomFactory::create()
{
	return ((Room *)(new MagicRoom()));
}