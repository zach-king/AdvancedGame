#ifndef MAGICROOM_H
#define MAGICROOM_H

#include "Room.h"

class MagicRoom : public Room
{
public:
	virtual Room* execute(RoomMap*, int &);
	virtual std::string getType();
};

#endif