#include<iostream>
#include<algorithm>
#include <random>
#include <set>

#include"RoomMap.h"
#include"NormalRoomFactory.h"
#include"MagicRoomFactory.h"


RoomMap::RoomMap()
{
	// Nothing
}

bool RoomMap::Initialize(std::string configFile, int &health)
{
	//Build room library and fill with Normal and Magic Room Factories
	roomLibrary["Normal"] = new NormalRoomFactory();
	roomLibrary["Magic"] = new MagicRoomFactory();

	return (LoadLevel(configFile.c_str(), health));
}

// Getter for inventory
std::vector<std::string> RoomMap::getInventory()
{
	return inventory;
}

// Adds item to inventory
void RoomMap::addItem(std::string itemName)
{
	inventory.push_back(itemName);
}

// Places items in inventory in a random *empty* Normal room
void RoomMap::disperseInventory()
{
	// Iterate over the inventory and place each item
	// in a random Normal Room that is empty
	for (auto itemIter = inventory.begin(); itemIter != inventory.end(); ++itemIter)
	{
		for (auto room : rooms)
		{
			// Originally contained an item and no longer does; also not the quit room
			if (room.second->getType() != "Magic" && room.second->getIdentifier() != "quit" && room.second->getItem() == "")
			{
				// Place the item in the room
				room.second->setItem(*itemIter);
			}
		}
	}

	// Finished dispersing items, now clear the inventory
	inventory.clear();
}

// Returns a pointer to next Room based off of transition
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


// Load level based off of XML configuration file.
// Note: this could be from the regular level file, 
// or from the savefile.
bool RoomMap::LoadLevel(const char* configFile, int &health)
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

	// Inventory and item pointers
	TiXmlElement* pInventXML = NULL;
	TiXmlElement* pItemXML = NULL;

	// Parse the puzzle XML object; get the root XML element
	pRootXML = levelConfig.FirstChildElement("Puzzle");

	// If <Puzzle> is not in config file, exit with error
	if (!pRootXML)
		return false;

	// Get health if given in the XML
	if (pRootXML->Attribute("health") != NULL)
		pRootXML->QueryIntAttribute("health", &health);

	// Parse the inventory out of XML file, if it exists
	pInventXML = pRootXML->FirstChildElement("Inventory");
	if (pInventXML)
	{
		// Clear the current inventory, since one exists in the config file
		inventory.clear();

		// Get the first Item element, and parse items, adding them to inventory
		pItemXML = pInventXML->FirstChildElement("Item");
		while (pItemXML)
		{
			inventory.push_back(pItemXML->Attribute("name"));
			pItemXML = pItemXML->NextSiblingElement("Item");
		}
	}

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

		// Check if this is the current room from the config file
		if (pRoomXML->Attribute("current") != NULL)
		{
			startRoom = newRoom;
			currentRoom = newRoom;
		}

		// Store the new Room in our rooms map
		rooms[newRoom->getIdentifier()] = newRoom;

		// Try to get the next <Room> XML element if available
		pRoomXML = pRoomXML->NextSiblingElement("Room");
	}

	// Everything completed successfully; return true
	return true;
}

// Save the current state of the game to an XML file
bool RoomMap::SaveLevel(const char* saveFile, int health)
{
	// Build the XML document
	TiXmlDocument saveDoc;

	// Add the Puzzle element
	TiXmlElement* root = new TiXmlElement("Puzzle");
	root->SetAttribute("health", health);
	saveDoc.LinkEndChild(root);

	// Pointer to be reused for elements
	TiXmlElement* elem;
	TiXmlElement* childElem;

	// Add the inventory
	elem = new TiXmlElement("Inventory");
	for (auto itemIter = inventory.begin(); itemIter != inventory.end(); ++itemIter)
	{
		// Keep making new <Item> elements, with the Item data
		childElem = new TiXmlElement("Item");
		childElem->SetAttribute("name", (*itemIter).c_str());
		elem->LinkEndChild(childElem);
	}
	root->LinkEndChild(elem);

	// Add the Room elements
	for (auto room : rooms)
	{
		// Set Room attributes
		elem = new TiXmlElement("Room");
		elem->SetAttribute("type", room.second->getType().c_str());
		elem->SetAttribute("condition", room.second->getCondition());
		elem->SetAttribute("name", room.second->getIdentifier().c_str());
		elem->SetAttribute("description", room.second->getDescription().c_str());
		elem->SetAttribute("item", room.second->getItem().c_str());

		// If current room, indicate such in save file;
		// This is used for loading later, so the player is 
		// placed in the room they left off at from the save
		if (room.second == currentRoom)
		{
			elem->SetAttribute("current", "yes");
		}

		// Create Neighbor children of Room
		for (auto neigh : room.second->getNeighbors())
		{
			childElem = new TiXmlElement("Neighbor");
			childElem->SetAttribute("transition", neigh.first.c_str());
			childElem->SetAttribute("target", neigh.second.c_str());
			elem->LinkEndChild(childElem);
		}
		root->LinkEndChild(elem);
	}

	// Save the XML to file
	return saveDoc.SaveFile(saveFile);
}

// Setter for currentRoom
void RoomMap::setCurrentRoom(Room* pRoom)
{
	currentRoom = pRoom;
}

// Setter for startRoom
void RoomMap::setStartRoom(Room* pRoom)
{
	startRoom = pRoom;
}

// Getter for startRoom
Room* RoomMap::getStartRoom()
{
	return startRoom;
}

// Randomize the rooms with the following conditions:
//		- each room exists only once in map
//		- doors are two-way (return to prev room with oposite direction)
//		- quit is always an option
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