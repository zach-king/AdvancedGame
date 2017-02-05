#ifndef ROOMMAP_H
#define ROOMMAP_H

#include<map>
#include<string>

#include"Room.h"
#include "RoomFactory.h"

#include"ThirdParty\tinyxml\tinystr.h"
#include"ThirdParty\tinyxml\tinyxml.h"

#include <vector>

class RoomMap
{
public:
	RoomMap();
	bool Initialize(std::string configFile, int &health);
	Room* findNext(Room*);
	void randomizeRooms();
	std::vector<std::string> getInventory();
	void addItem(std::string);
	void disperseInventory();
	bool SaveLevel(const char*, int);
	void setCurrentRoom(Room*);
	void setStartRoom(Room*);
	Room* getStartRoom();

private:
	std::map<std::string, RoomFactory*> roomLibrary;
	std::map<std::string, Room*> rooms;

	// Player inventory
	std::vector<std::string> inventory;

	// Private XML level loading instructions
	bool LoadLevel(const char*, int&);
	Room* startRoom;
	Room* currentRoom;
};

#endif