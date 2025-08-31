#include "GameBoard.h"
#include "Coord.h"
#include "Ship.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;
// GameBoard()
// INPUTS: None (None)
// OUTPUTS: None (None)
// Depends on: None
// initialises game board
GameBoard::GameBoard(vector<Ship>& allShips, string boardID) {
	_gameState = {
		{"~","~","~","~","~","~","~","~","~","~"},
		{"~","~","~","~","~","~","~","~","~","~"},
		{"~","~","~","~","~","~","~","~","~","~"},
		{"~","~","~","~","~","~","~","~","~","~"},
		{"~","~","~","~","~","~","~","~","~","~"},
		{"~","~","~","~","~","~","~","~","~","~"},
		{"~","~","~","~","~","~","~","~","~","~"},
		{"~","~","~","~","~","~","~","~","~","~"},
		{"~","~","~","~","~","~","~","~","~","~"},
		{"~","~","~","~","~","~","~","~","~","~"}
	};
	_playerHits = {};
	_playerMisses = {};
	_allOccupiedSpaces = calcAllOccupiedSpaces(allShips);
	_boardID = boardID;
}
// these getPlayerHitIndex and getPlayerMissIndex are designed for an iterator to display a list
// if an error occurs, you get the error coordinate
string GameBoard::getBoardID() 
{
	return _boardID;
}
Coord GameBoard::getPlayerHitIndex(int index) 
{
	if (index < _playerHits.size()) 
	{
		return _playerHits[index];
	}
		return Coord(-1, -1);
}
Coord GameBoard::getPlayerMissIndex(int index) 
{
	if (index < _playerMisses.size()) 
	{
		return _playerMisses[index];
	}
	return Coord(-1, -1);
}
// getAIhits and getAIMisses return the whole list, since the AI is likely to need the whole list.
vector<Coord> GameBoard::calcAllOccupiedSpaces(vector<Ship>& allShips)
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
vector<Coord> GameBoard::getAllOccupiedSpaces() 
{
	return _allOccupiedSpaces;
}
//addPlayerShell() 
//INPUTS: Pos (Coord), allShips(vector<Ship>&)
//OUTPUTS: None (none)
//Depends on: Coord class, ship class, getAllOccupiedSpaces
//This automatically does hit checking, adding it to a list as appropriate
bool GameBoard::AddPlayerShell(Coord Pos, vector<Ship>& allShips) 
{
	int index = -1;
	vector<Coord> OccupiedSpaces = _allOccupiedSpaces;
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
	
			_playerHits.push_back(Pos);
		
		
	}
	else 
	{
	
			_playerMisses.push_back(Pos);
	
		
	}
	return false;
	
}
// note: Depends on AddPlayerShell()
void GameBoard::prepareDisplayBoard(bool playerBoard)
{
	if(playerBoard)
	{ 
		// this requires repitition. We are indexing through lists of differing sizes.
		for(int i = 0; i < _playerMisses.size(); i++)
		{
			_gameState[_playerMisses[i].getX()][_playerMisses[i].getY()] = "X";
		}
		for (int i = 0; i < _playerHits.size(); i++)
		{
			_gameState[_playerHits[i].getX()][_playerHits[i].getY()] = "h";
		}
	}
	
}
void GameBoard::addShips(vector<Ship>& allShips)
{
	const map<string, string> hitRef = {
		{"P","p"},
		{"S","s"},
		{"C","c"},
		{"B","b"},
		{"A","a"}
	};
	vector<Coord> hitList;
		hitList = _playerHits;
	
	for (int i = 0; i < allShips.size(); i++)
	{
		vector<Coord> shipOccu = allShips[i].getOccupiedCoords();
		
		for (int j = 0; j < shipOccu.size(); j++) 
		{
			Coord CurrentCoord = shipOccu[j];
			//cout <<"X"<< CurrentCoord.getX() <<"Y" << CurrentCoord.getY() <<"type" <<allShips[i].getType()<< endl;

					if(find(hitList.begin(), hitList.end(),CurrentCoord) != hitList.end())
					{
						_gameState[CurrentCoord.getX()][CurrentCoord.getY()] = hitRef.at(allShips[i].getType());
					}
					else 
					{
						_gameState[CurrentCoord.getX()][CurrentCoord.getY()] = allShips[i].getType();
					}
			
			
		}
	}
}
void GameBoard::displayBoard()
{
	cout << "  ABCDEFGHIJ" << endl;
	const string Xref = "0123456789";
	string out = "";
	for(int i = 0; i < Xref.size(); i++) 
	{	
		out = "";
		out += Xref[i];
		out += " ";
		for (int j = 0; j < _gameState[i].size(); j++)
		{
			out += _gameState[i][j];
		}
		cout << out << endl;
	}
}
vector<Ship> GameBoard::getAllShips()
{
	return _allShips;
}
/*
Inputs: allShips (vector<Ship>&)
Outputs (Bool)
Depends on: getOccupiedCoords()
Checks if two or more ships occupy the same space
*/

vector<Ship> GameBoard::playerUI()
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
	   if(!Ship::validateShips(allShips))
	   {
		   cout << "Invalid configuration detected!" << endl;
		   return { Ship("Error",-1,-1, false) };
	   }
		std::cout << "good news: your setup is valid! I will draw your layout now." << endl;
		prepareDisplayBoard(true);
		addShips(allShips);
		displayBoard();
	
		// TEST LAYOUT: Patrol: D2 |, Submarine: E5 -, Cruiser: F8 | Battleship: D5 | cArrier: I5 -
		// use the above for testing
	}
	_allShips = allShips;
	return allShips;
}