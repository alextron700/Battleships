#include "Ship.h"
#include <string>
#include <vector>
#include "Coord.h"
#include <iostream>
using namespace std;
/*
 Ship
 INPUTS: Type (String), posX ( int), posY (int), length (int)
 OUTPUTS: none
 Depends on: None
 The Constructor for the Ship class
*/
Ship::Ship(string type, int posX, int posY, bool facing)
{
  _type = type;
  _posX = posX;
  _posY = posY;
  _facing = facing;
  _length = shipLength.at(type);
  _health = _length;
}

/*
getXpos()
INPUTS: None
OUTPUTS: _posX ( int)
Depends on: NONE
Returns the X position of a Ship.
*/
int Ship::getXpos() {
	return _posX;
}
/*
getYpos()
INPUTS: None
OUTPUTS: _posY ( int)
Depends on: NONE
Returns the Y position of a Ship.
*/
int Ship::getYpos() {
	return _posY;
}
/*
getFacing()
INPUTS: None
OUTPUTS: _facing (bool)
Depends on: NONE
Returns the facing of a Ship.
true = Up/down
false = Left/right
*/
bool Ship::getFacing() {
	return _facing; //
}
/*
getHealth()
INPUTS: None
OUTPUTS: _health ( int)
Depends on: NONE
Returns the remaining hits of a Ship.
*/
int Ship::getHealth() {
	return _health;
}
/*
getType()
INPUTS: None
OUTPUTS: _type (string)
Depends on: NONE
Returns the type of a Ship.
*/
string Ship::getType() {
	return _type;
}
int Ship::getLength() {
	return _length;
}
/*
hit()
INPUTS: posX ( int), posY ( int ), takeHealth (Bool)
OUTPUT: See description
Depends on: getXPos, getYpos, getFacing, getLength, getHealth
OUTPUTS:
If takeHealth is true:
hit detected: Ship's remaining health
ship sunk: 0
no ship: -1
if takeHealth is false:
ship found: 7 
ship not found: 6
			if (shipH > 0) {
				if (takeHealth) {
					_health--;
					return _health;// return the ship's new health (hit)
				}
				else {
					return 7; // Why 7? -1 and 0 are already valid results, and 1-5 are already taken (from legit remaining health values)
				} // so I used clearly invalid health numbers to indicate found and not found ( Not taking health) this is the same reason
				// I also use 6. some numbers just outside the valid range, to not conflict with other results.
			}
			else{
				return 0; // return Ship Sank
			}
		}
		else {
			if (takeHealth) {
				return -1; // return miss
			}
			else {
				return 6;
			}
		}
*/
bool Ship::hitCheck(int posX, int posY)
{
	int shipX = getXpos();
	int shipY = getYpos();
	bool shipF = getFacing();
	int shipL = getLength();
	int shipH = getHealth();
	if (!shipF)
	{
		if (shipX - posX <= shipL && shipX >= posX && shipY == posY) {
			return true;
		}
	}
	else
	{
		if (shipX == posX && shipY >= posY && shipY - posY <= shipL) {
			return true;
		}
	}
	return false;
}
int Ship::hit(int posX, int posY) 
{
	bool isHit = hitCheck(posX, posY);
	if (isHit) 
	{
		if (_health > 0) 
		{
			_health--;
		}
		return _health;
	}
	else 
	{
		return -1;
	}
}
/*
getOccupiedCoords()
INPUTS: None (none)
OUTPUTS: output (vector<Coord>)
Depends on: None
Returns a list of spaces a ship occupies.
*/
std::vector<Coord> Ship::getOccupiedCoords()
{

	vector<Coord> output = {};

	for (int i = 0; i < _length; i++)
	{

		if (_facing)
		{

			output.push_back(Coord(_posX, _posY - i));

		}
		else 
		{

			output.push_back(Coord(_posX - i, _posY));

		}

	}

	return output;

}
bool Ship::isValidType(string type)
{
	return shipLength.contains(type);
}
bool Ship::IntersectCheck(vector<Ship>& allShips)
{
	std::vector<Coord> allCoords;
	std::set<Coord> uniqueCoords;

	for (int i = 0; i < allShips.size(); i++) {
		// Get all coordinates for the current ship.
		std::vector<Coord> shipBodyCoords = allShips[i].getOccupiedCoords(); // A new function you need to add to your Ship class

		// Add each coordinate to both containers
		for (const Coord& coord : shipBodyCoords) {
			allCoords.push_back(coord);
			uniqueCoords.insert(coord);
		}
	}

	if (allCoords.size() > uniqueCoords.size()) {
		return true; // Duplicates found
	}
	return false; // No duplicates
}
bool Ship::isValid()
{
	//check the edge of the board. Since ships get drawn from right to left, there is no need to check
	// the right edge. Position validation handles the right edge ( I.E, it should'nt let you place ship
	// that goes beyond the right edge anyway)
	if (_posX - _length + 1 < 0 && _facing == false)
	{
		return false;
	}

	// check the top edge of the board. Since ships get drawn from bottom to top, there is no need to check
	// the bottom edge. Position Validation also handles the bottom edge. It shouldn't be possible to have
	// ships beyond the bottom edge anyway.
	if (_posY - _length + 1 < 0 && _facing == true)
	{
		return false;
	}
	if (!isValidType(_type))
	{
		return false;
	}
	if(_type == "Error")
	{
		return false;
	}
	return true;
}
bool Ship::validateShips(vector<Ship> allShips)
{
	
	for (int i = 0; i < allShips.size(); i++)
	{


		if (!allShips[i].isValid())
		{
		
			cout << "Looks like the password was invalid" << endl;
			return false;
			
		}
		
		
	}



		return !IntersectCheck(allShips);
	
}