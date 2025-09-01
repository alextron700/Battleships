#include "Player.h"
#include <string>
#include <iostream>
using namespace std;
Player::Player()
{
	_GBHits = {};
	_GBMisses = {};
	_HitDiagram = {
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~"
	};

}
//CalcAllOccupiedSpaces
//INPUTS: allShips (vector<Ship>&)
//OUTPUTS: OccupiedSpaces (vector<Coord>)
//Depends on: Ship:getOccupiedCoords
// Calculates all the spaces occupied by the given list of ships
vector<Coord> Player::calcAllOccupiedSpaces(vector<Ship>& allShips)
{

	vector<Coord> OccupiedSpaces = {};
	// this takes all the spaces occupied by ships into a vector
	for (int i = 0; i < allShips.size(); i++)
	{
		vector<Coord> Occu = allShips[i].getOccupiedCoords();
		for (int j = 0; j < allShips[i].getOccupiedCoords().size(); j++) {
			OccupiedSpaces.push_back(Occu[j]);
		}
	}
	return OccupiedSpaces;
}
//AddPLayerShell
//INPUTS: Pos (Coord), allShips(vector<Ship>&)
//OUTPUTS: Bool
// Depends on: calcAllOccupiedSpaces()
// Automatically determines if a shell is a hit or miss, and puts it in the respective list
bool Player::AddPlayerShell(Coord Pos, vector<Ship>& allShips)
{
	int index = -1;
	vector<Coord> OccupiedSpaces = calcAllOccupiedSpaces(allShips);
	for (int i = 0; i < OccupiedSpaces.size(); i++)
	{
		if (OccupiedSpaces[i] == Pos)
		{
			index = i;
			break;
		}
	}
	if (index >= 0)
	{

		_GBHits.push_back(Pos);
		return true;

	}
	else
	{

		_GBMisses.push_back(Pos);


	}
	return false;

}
// getPlayerHits and getPlayerMisses
// INPUTS: NONE
// OUTPUTS:
// GetPlayerMisses: _GBMisses (vector<Coord>)
// GetPlayerHits: _GBHits (vector<Coord>)
// Depends on: None
// returns their respective lists
vector<Coord> Player::getPlayerHits()
{
	return _GBHits;
}
vector<Coord> Player::getPlayerMisses()
{
	return _GBMisses;
}
//drawHits
// INPUTS: None(None)
// OUTPUTS: None(None)
// Depends on: None
// Draws the diagram for the palyer to see their hits and misses
void Player::drawHits()
{


	for (int i = 0; i < _GBMisses.size(); i++)
	{
		_HitDiagram[_GBMisses[i].getX()][_GBMisses[i].getY()] = 'M';
	}
	for(int i = 0; i< _GBHits.size(); i++)
	{
		_HitDiagram[_GBHits[i].getX()][_GBHits[i].getY()] = 'H';
	}
	cout << " ABCDEFGHIJ" << endl;
	for (int i = 0; i < _HitDiagram[0].size(); i++)
	{
		cout << i << _HitDiagram[i] << endl;
	}
}
// Main Will have to call drawBoard() On it's own
bool Player::coordIsUnique(Coord input)
{
	return (find(_GBHits.begin(), _GBHits.end(), input) == _GBHits.end()) && (find(_GBMisses.begin(), _GBMisses.end(), input) == _GBMisses.end());
}
int Player::PlayerShellUI(vector<Ship>& allShips, string GBID = "P1")
{
	map<string, string> convertShipID = {
		{"P","Patrol"},
		{"S", "Submarine"},
		{"C", "Cruiser"},
		{"B", "Battleship"},
		{"A", "Carrier"}
	};
	cout << "Begin "<<GBID<<" turn!" << endl;
	cout << "Known information about Enemy:" << endl;
	drawHits();
	cout << "Pick a position to shoot:" << endl;
	string GBShellInput;
	getline(cin, GBShellInput);
	Coord shell = Coord(GBShellInput);
	
	for(int i = 0; i < allShips.size(); i++)
	{
		// I leave this here, because It's a good showing of my thinking, and figuing out an improvement
		// if (allShips[i].hitCheck(shell.getX(), shell.getY()) && coordIsUnique(shell))
		//{ 
		//	allShips[i].hit(shell.getX(), shell.getY());
		//	cout << "Hit!" << endl;
		//	AddPlayerShell(shell,allShips);
		//	if(allShips[i].getHealth() == 0)
		//	{
		//		cout << "Sank Opponent's " << convertShipID.at(allShips[i].getType()) << "!" <<endl;
		//	}
		//	return 0;
		//}else if(!coordIsUnique(shell))
	//	{
		//	cout << "Looks like you tried to enter a duplicate coordinate. try again!" << endl;
		//Player::PlayerShellUI(allShips);
		//	return 0;
		//}
		//else
		//{
		//	cout << "Miss!" << endl;
		//	AddPlayerShell(shell, allShips);
		//	return -1;
		//}
		if(coordIsUnique(shell))
		{
			if (AddPlayerShell(shell, allShips)) 
			{
				allShips[i].hit(shell.getX(), shell.getY());
				cout << "Hit!" << endl;
				//if (allShips[i].getHealth() == 0)
				//{
				//	cout << "Sank Opponent's " << convertShipID.at(allShips[i].getType()) << "!" << endl;
				//}
				return 0;
			}
			else
			{
				std::cout << "Miss!" << endl;
				AddPlayerShell(shell, allShips);
				return -1;
			}
		}
		else
		{
			cout << "Looks like you tried to enter a duplicate coordinate. try again!" << endl;
			Player::PlayerShellUI(allShips);
			return 0;
		}





	}
	
}
vector<Ship> Player::GBUI()
{

	//std::cout << "you will get to view the board once you've placed all your ships, and I do some validating." << endl;

	string ShipToSpawn;
	vector<Ship> allShips = {};
	set<string> setOfAllShips = {};

	while (allShips.size() < 5) {
		string pos;
		std::cout << "Begin by positioning your ships, with an X position (0-9), and a Y position (A-J)" << endl;
		std::cout << "Examples Of Valid Coordinates are: d5, E9, 2B, 0a. Examples of Invalid Coordinates: 2k, 12b, b-1, -3B" << endl;
		std::cout << "This is what your board looks like: (by the way, you should enter a coordinate now)" << endl;
		addShips(allShips);
		displayBoard();
		std::getline(cin, pos);
		Coord shipPos = Coord(pos);
		if (!shipPos.getValid()) {
			std::cout << "Nice Try!" << endl;
			continue;
		}
		std::cout << "Pick an orientation: (Valid inputs are: | or -) " << endl;
		string hdg;
		bool shipDir;
		std::getline(cin, hdg);
		if (hdg == "|") {
			shipDir = false;
		}
		else if (hdg == "-") {
			shipDir = true;
		}
		else {
			std::cout << "The only valid inputs are: | or -" << endl;
			continue;
		}
		std::cout << "Now pick a type of ship Valid Selections are: P (patrol boat), S (submarine), C (Cruiser), B (Battleship), A (carrier). You'll need one of each." << endl;
		std::cout << " I won't let you proceed until you've place all five ships. If you try to place two of the same ship, I won't let you. Note: You MUST use CAPITALS." << endl;
		std::getline(cin, ShipToSpawn);
		if (Ship::isValidType(ShipToSpawn) && setOfAllShips.find(ShipToSpawn) == setOfAllShips.end()) {
			setOfAllShips.insert(ShipToSpawn);
			allShips.push_back(Ship(ShipToSpawn, shipPos.getX(), shipPos.getY(), shipDir));
		}
		else
		{
			std::cout << "Nice Try!" << endl;
			continue;
		}



		//std::cout << " You have placed all five ships. Allow me to check nothing's wrong with your layout" << endl;
		if (!Ship::validateShips(allShips))
		{
			cout << "Invalid configuration detected!" << endl;
			return { Ship("Error",-1,-1, false) };
		}
		std::cout << "good news: your setup is valid! I will draw your layout now." << endl;
		addShips()
		

		// TEST LAYOUT: Patrol: D2 |, Submarine: E5 -, Cruiser: F8 | Battleship: D5 | cArrier: I5 -
		// use the above for testing
	}
	_allShips = allShips;
	return allShips;
}