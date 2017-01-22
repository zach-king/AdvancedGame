#include<iostream>
#include<algorithm>
#include <random>
#include <set>

#include"RoomMap.h"
#include"NormalRoomFactory.h"
#include"MagicRoomFactory.h"


RoomMap::RoomMap()
{
	//Nothing
}

bool RoomMap::Initialize(std::string configFile)
{
	//Build room library
	roomLibrary["Normal"] = new NormalRoomFactory();
	roomLibrary["Magic"] = new MagicRoomFactory();

	if (LoadLevel(configFile.c_str()))
		return true;
	else
		return false;
}

Room* RoomMap::findNext(Room* room)
{
	Room* next;
	std::map<std::string, Room*>::iterator miter;

	// If room is a valid pointer, search for its next 
	// Otherwise, search for the starting room
	if (room != NULL)
		miter = rooms.find(room->next());
	else
		miter = rooms.find("start");

	// If next is found, return the Room pointer to it
	// Otherwise, return NULL
	if (miter != rooms.end())
		next = miter->second;
	else
		next = NULL;

	return next;
}


bool RoomMap::LoadLevel(const char* configFile) {

	// Create the XML document
	TiXmlDocument levelConfig(configFile);
	if (!levelConfig.LoadFile())
	{
		std::string error = levelConfig.ErrorDesc();
		return false;
	}
	TiXmlHandle hDoc(&levelConfig);

	// Set-up the Root, Room, and neighbor pointers for data acquisition
	TiXmlElement* pRootXML = NULL;
	TiXmlElement* pRoomXML = NULL;

	// Parse the puzzle object
	pRootXML = levelConfig.FirstChildElement("Puzzle");

	// Exit with failure if this object is unavailable
	if (!pRootXML)
		return false;

	//------------------------------------------
	// Build the Rooms of the game space
	//------------------------------------------

	// Parse the first room object
	pRoomXML = pRootXML->FirstChildElement("Room");

	// Exit with failure if this object is unavailable
	if (!pRoomXML)
		return false;

	// Set-up up object
	Room* tmp = NULL;

	while (pRoomXML)
	{
		// Create the appropriate object type
		// tmp = roomLibrary[pRoomXML->Attribute("type")]->create();
		tmp = (*roomLibrary.find(pRoomXML->Attribute("type"))).second->create();

		// Intialize this object
		tmp->Initialize(pRoomXML);

		// Add the initialized object to the game space
		rooms[tmp->getIdentifier()] = tmp;

		// Grab the next if available
		pRoomXML = pRoomXML->NextSiblingElement("Room");
	}

	return true;
}

void RoomMap::randomizeRooms()
{
	// Setup the RNG (Random Number Generator)
	static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<int> ud(0, rooms.size() * 2);

	// Clear all neighbors
	for (auto room : rooms)
	{
		room.second->clearNeighbors();
	}

	std::map<std::string, std::string> neighbors;

	// Iterate over rooms
	for (auto room : rooms)
	{
		//skip the "quit" room
		if (room.second->getIdentifier() != "quit")
		{
			//keep doing this until I have at least one neighbor
			do
			{
				//get the neighbors for the current room.
				neighbors = room.second->getNeighbors();
				//always have the quit option.
				neighbors["q"] = "quit";

				//Now we need to make a lits of possible neighbors.
				std::map<std::string, int> possibleNeighbors;

				std::map<std::string, std::string>::iterator neighborIter;

				//for every direction that does not have a connection, select a randomroom.
				neighborIter = neighbors.find("a");
				if (neighborIter == neighbors.end())
				{
					possibleNeighbors["a"] = ud(e);
				}
				neighborIter = neighbors.find("w");
				if (neighborIter == neighbors.end())
				{
					possibleNeighbors["w"] = ud(e);
				}
				neighborIter = neighbors.find("d");
				if (neighborIter == neighbors.end())
				{
					possibleNeighbors["d"] = ud(e);
				}
				neighborIter = neighbors.find("s");
				if (neighborIter == neighbors.end())
				{
					possibleNeighbors["s"] = ud(e);
				}
				//set up neighbor connection
				for (auto possibleNeighbor : possibleNeighbors)
				{
					bool skipMe = false;

					std::map<std::string, Room*>::iterator roomIter = rooms.begin();
					//only a connection if the possible neighbor number is a room number
					if (possibleNeighbor.second < rooms.size())
					{
						//advance the iterator to the room we want to connect to.
						for (int i = 0; i < possibleNeighbor.second; i++)
						{
							roomIter++;
						}
						//make sure I am not connecting to myself or to the "quit" room
						if (roomIter->second->getIdentifier() == "quit" || roomIter->second->getIdentifier() == room.second->getIdentifier())
						{
							skipMe == true;
						}
						//connect the rooms.
						std::map<std::string, std::string> curRoomNeighbors = roomIter->second->getNeighbors();
						if (!skipMe && possibleNeighbor.first == "a")
						{
							//make sure there isn't a neighbor already using this wall.
							if (curRoomNeighbors.find("d") == curRoomNeighbors.end())
							{
								roomIter->second->addNeighbor("d", room.second->getIdentifier());
								room.second->addNeighbor("a", roomIter->second->getIdentifier());
							}
						}
						if (!skipMe && possibleNeighbor.first == "d")
						{
							if (curRoomNeighbors.find("a") == curRoomNeighbors.end())
							{
								roomIter->second->addNeighbor("a", room.second->getIdentifier());
								room.second->addNeighbor("d", roomIter->second->getIdentifier());
							}
						}
						if (!skipMe && possibleNeighbor.first == "s")
						{
							if (curRoomNeighbors.find("w") == curRoomNeighbors.end())
							{
								roomIter->second->addNeighbor("w", room.second->getIdentifier());
								room.second->addNeighbor("s", roomIter->second->getIdentifier());
							}
						}
						if (!skipMe && possibleNeighbor.first == "w")
						{
							if (curRoomNeighbors.find("s") == curRoomNeighbors.end())
							{
								roomIter->second->addNeighbor("s", room.second->getIdentifier());
								room.second->addNeighbor("w", roomIter->second->getIdentifier());
							}
						}
					}
				}
			} while (room.second->getNeighbors().size() == 0);
		}
	}
}

Room* RoomMap::getRoom(std::string ident)
{
	auto result = rooms.find(ident);
	if (result != rooms.end())
		return result->second;
	else
		return NULL;
}