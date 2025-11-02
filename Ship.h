#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
#include "Coord.h"
// represents a ship on a GameBoard.
using namespace std;

enum Facing
{
	Horizontal,
	Vertical
};

class Ship
{
public:
	Ship(string type, int posX, int posY, Facing facing);
	Ship() { _type = "Error", _posX = -1, _posY = -1, _facing = Horizontal; };
	int getXpos();
	int getYpos();
	Facing getFacing();
	int getLength();
	int getHealth();
	bool hitCheck(int Xpos,int Ypos); 
	string getType();
	int hit(int posX, int posY);
	vector<Coord> getOccupiedCoords();
	bool isValid();
	static bool isValidType(string type);
	static bool validateShips(vector<Ship> allShips);
	static bool IntersectCheck(vector<Ship>& allShips);
private:
	string _type;
	static inline const map<string, int> shipLength = {
	{"P",2},
	{"S",3},
	{"C",3},
	{"B",4},
	{"A", 5},
	{"Error", -1}
	};
	int _posX;
	int _posY; // Defined by the back of the ship Y= Up/down, X= Left/right
	Facing _facing; // true = up/down false = left/right 
	int _length;
	int _health;
};
