#ifndef NORMALROOM_H
#define NORMALROOM_H

#include "Room.h"

class NormalRoom : public Room
{
public:
	virtual Room* execute(RoomMap*, int &);
	virtual std::string getType();
};

#endif