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
	bool Initialize(std::string configFile);
	Room* findNext(Room*);
	void randomizeRooms();
	std::vector<std::string> getInventory();
	void addItem(std::string);
	void disperseInventory();

private:
	std::map<std::string, RoomFactory*> roomLibrary;
	std::map<std::string, Room*> rooms;

	// Player inventory
	std::vector<std::string> inventory;

	// Private XML level loading instructions
	bool RoomMap::LoadLevel(const char* configFile);
};

#endif