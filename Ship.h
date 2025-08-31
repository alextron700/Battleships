#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
#include "Coord.h"
using namespace std;

class Ship
{
public:
	Ship(string type, int posX, int posY, bool facing);
	
	int getXpos();
	int getYpos();
	bool getFacing();
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
	static inline const const map<string, int> shipLength = {
	{"P",2},
	{"S",3},
	{"C",3},
	{"B",4},
	{"A", 5},
	{"Error", -1}
	};
	int _posX;
	int _posY; // Defined by the back of the ship Y= Up/down, X= Left/right
	bool _facing; // true = up/down false = left/right 
	int _length;
	int _health;
};
