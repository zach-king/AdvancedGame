#include "MagicRoom.h"
#include "Room.h"
#include "RoomMap.h"

#include <iostream>

Room* MagicRoom::execute(RoomMap *roomMap, int &health)
{
	std::cout << "You hear loud grinding sounds and you feel your strength restored!" << std::endl;
	health += 2;
	roomMap->randomizeRooms();

	// Display the screen output
	std::cout << "View:\t" << description << std::endl;
	std::cout << "Health: " << health << std::endl << std::endl;
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
	// but to counter health decrement, increment it here.
	// This keeps us in the same place. Like walking into a wall...
	if (neighbors.find(transition) == neighbors.end())
	{
		health++;
		return this;
	}

	// Get the next room
	return roomMap->findNext(this);
}