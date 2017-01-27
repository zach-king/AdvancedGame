#ifndef ROOM_H
#define ROOM_H

#include<map>
#include<string>
#include"definitions.h"

#include"ThirdParty\tinyxml\tinystr.h"
#include"ThirdParty\tinyxml\tinyxml.h"

//Forward declaration
class RoomMap;

class Room
{
public:
	Room();
	~Room();
	bool Initialize(TiXmlElement*);//char,END_CONDITION,std::string,std::string);
	virtual Room* execute(RoomMap*, int &) = 0;
	bool finish();
	std::string next();

	//Accessor methods
	void setIdentifier(std::string);
	void setDescription(std::string);
	std::string getIdentifier();
	END_CONDITION getCondition();
	void  addNeighbor(std::string, std::string);
	void clearNeighbors();
	std::map<std::string, std::string> getNeighbors();
	bool getCanHaveItem();
	std::string getItem();
	void setItem(std::string);

protected:
	std::string transition;
	END_CONDITION condition;
	std::string identifier;
	std::string description;
	std::map<std::string, std::string> neighbors;
	std::string item;
	bool canHaveItem;
};

#endif