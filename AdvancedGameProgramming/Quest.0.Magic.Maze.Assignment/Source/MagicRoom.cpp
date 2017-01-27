#include "MagicRoom.h"
#include "Room.h"
#include "RoomMap.h"

#include <iostream>
#include <vector>

Room* MagicRoom::execute(RoomMap *roomMap, int &health)
{
	std::cout << "You hear loud grinding sounds and you feel your strength restored!" << std::endl;
	if (!roomMap->getInventory().empty())
	{
		std::cout << "In the midst of the commotion, your items have been scattered across the dungeon!" << std::endl;
	}

	health += 2;
	roomMap->randomizeRooms();

	// Display the screen output
	std::cout << "View:\t" << description << std::endl;
	std::cout << "Health: " << health << std::endl << std::endl;

	// Randomly disperse the player's items 
	roomMap->disperseInventory();

	// Display inventory
	std::cout << "Inventory:" << std::endl;
	std::vector<std::string> items = roomMap->getInventory();
	for (auto itemIter = items.begin(); itemIter != items.end(); ++itemIter)
	{
		std::cout << "\t" << *itemIter << std::endl;
	}

	std::cout << "Available Moves: ";
	for each (auto neighbor in neighbors)
	{
		std::cout << neighbor.first << " ";
	}
	std::cout << std::endl << std::endl;
	std::cout << "Select Move: ";

	// Get the user input transition
	std::cin >> transition;

	// Validate transition; if invalid,
	// return same Room, because we didn't move
	// but to counter health increment, decrement it here.
	// This keeps us in the same place. Like walking into a wall...
	if (neighbors.find(transition) == neighbors.end())
	{
		health -= 2;
		return this;
	}

	// Get the next room
	return roomMap->findNext(this);
}