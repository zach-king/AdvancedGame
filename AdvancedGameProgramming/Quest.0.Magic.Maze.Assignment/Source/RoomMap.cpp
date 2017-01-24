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
	//Build room library and fill with Normal and Magic Room Factories
	roomLibrary["Normal"] = new NormalRoomFactory();
	roomLibrary["Magic"] = new MagicRoomFactory();

	return (LoadLevel(configFile.c_str()));
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
		return miter->second;
	return NULL;
}


bool RoomMap::LoadLevel(const char* configFile)
{
	// Create the XML document object and 
	// Check if it loaded without trouble
	TiXmlDocument levelConfig(configFile);
	if (!levelConfig.LoadFile())
	{
		std::string error = levelConfig.ErrorDesc();
		return false;
	}

	// Root and room XML room pointers
	TiXmlElement* pRootXML = NULL;
	TiXmlElement* pRoomXML = NULL;

	// Parse the puzzle XML object; get the root XML element
	pRootXML = levelConfig.FirstChildElement("Puzzle");

	// If <Puzzle> is not in config file, exit with error
	if (!pRootXML)
		return false;

	// Build the Rooms of the game space.
	// Parse the first <Room> object from the root object
	pRoomXML = pRootXML->FirstChildElement("Room");

	// Exit with failure if this object is unavailable
	if (!pRoomXML)
		return false;

	// Pointer for storing each new Room
	Room* newRoom = NULL;

	// Loop while we still have <Room> tags in the config file to parse
	while (pRoomXML)
	{
		// Create the new Room from the roomLibrary, using the type
		// specified in the XML config file (i.e. type Magic or Normal).
		// Reminder: roomLibrary is a map of <std::string, ObjectFactory*>
		// Where the string is the type. Also validate the type.
		auto result = roomLibrary.find(pRoomXML->Attribute("type"));
		if (result == roomLibrary.end())
			return false; // invalid type
		newRoom = result->second->create();

		// Intialize this object with the given XML <Room> element pRoomXML
		// Validates the initialization was successful too
		if (!newRoom->Initialize(pRoomXML))
			return false;

		// Store the new Room in our rooms map
		rooms[newRoom->getIdentifier()] = newRoom;

		// Try to get the next <Room> XML element if available
		pRoomXML = pRoomXML->NextSiblingElement("Room");
	}

	// Everything completed successfully; return true
	return true;
}

void RoomMap::randomizeRooms()
{
	// Setup the RNG (Random Number Generator)
	// The ud is 0-rooms.size*2 because we don't 
	// want every single wall to have a door necessarily.
	// In fact, that's probably impossible...
	static std::random_device rDev;
	static std::default_random_engine e(rDev());
	static std::uniform_int_distribution<int> ud(0, rooms.size() * 2);

	// Clear all neighbors for each room
	for (auto room : rooms)
		room.second->clearNeighbors();

	std::map<std::string, std::string> neighbors;

	// Iterate over rooms
	for (auto room : rooms)
	{
		// Skip the quit room
		if (room.second->getIdentifier() == "quit")
			continue;

		// Do until the current room has at least 1 neighbor
		do
		{
			// Get current room's neighbors
			neighbors = room.second->getNeighbors();

			// Map for storing empty neighbors (walls with no connection)
			std::map<std::string, int> emptyNeighbors;
			std::map<std::string, std::string>::iterator neighborIter;

			// If a wall doesn't have a connected Room, 
			// select a random Room #
			neighborIter = neighbors.find("a");
			if (neighborIter == neighbors.end())
			{
				emptyNeighbors["a"] = ud(e);
			}
			neighborIter = neighbors.find("w");
			if (neighborIter == neighbors.end())
			{
				emptyNeighbors["w"] = ud(e);
			}
			neighborIter = neighbors.find("d");
			if (neighborIter == neighbors.end())
			{
				emptyNeighbors["d"] = ud(e);
			}
			neighborIter = neighbors.find("s");
			if (neighborIter == neighbors.end())
			{
				emptyNeighbors["s"] = ud(e);
			}
			// Loop through empty neighbors and 
			// make connections where possible
			for (auto emptyNeighbor : emptyNeighbors)
			{
				std::map<std::string, Room*>::iterator roomIter = rooms.begin();

				// Thanks to the RNG we set up, some room #'s are out of range
				// and invalid room #'s. So only use valid #'s. Skip the invalid.
				if (emptyNeighbor.second >= rooms.size())
					continue;

				// Move the iter to point to the random #th Room
				for (int i = 0; i < emptyNeighbor.second; i++)
					++roomIter;

				// Ignore self and quit rooms
				if (roomIter->second->getIdentifier() == "quit" || roomIter->second->getIdentifier() == room.second->getIdentifier())
					continue;

				// Get current neighbors for the random #th room and 
				// make the appropriate connection where possible
				std::map<std::string, std::string> curNeighbors = roomIter->second->getNeighbors();
				if (emptyNeighbor.first == "a")
				{
					// Only one door per wall, so make sure it's not already in use
					if (curNeighbors.find("d") == curNeighbors.end())
					{
						roomIter->second->addNeighbor("d", room.second->getIdentifier());
						room.second->addNeighbor("a", roomIter->second->getIdentifier());
					}
				} // repeated pattern...
				if (emptyNeighbor.first == "d")
				{
					if (curNeighbors.find("a") == curNeighbors.end())
					{
						roomIter->second->addNeighbor("a", room.second->getIdentifier());
						room.second->addNeighbor("d", roomIter->second->getIdentifier());
					}
				}
				if (emptyNeighbor.first == "s")
				{
					if (curNeighbors.find("w") == curNeighbors.end())
					{
						roomIter->second->addNeighbor("w", room.second->getIdentifier());
						room.second->addNeighbor("s", roomIter->second->getIdentifier());
					}
				}
				if (emptyNeighbor.first == "w")
				{
					if (curNeighbors.find("s") == curNeighbors.end())
					{
						roomIter->second->addNeighbor("s", room.second->getIdentifier());
						room.second->addNeighbor("w", roomIter->second->getIdentifier());
					}
				}
			}
		} while (room.second->getNeighbors().size() == 0);
	}
}