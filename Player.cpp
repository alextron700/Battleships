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
	_gameState = {
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
		for (int j = 0; j < Occu.size(); j++) {
			OccupiedSpaces.push_back(Occu[j]);
		}
	}
	return OccupiedSpaces;
}
// determines which side has won, if a win is even detected
int Player::determineWin(vector<Ship> p1Ships, vector<Ship> p2Ships)
{
	int GBHPsum = 0;
	int AIHPsum = 0;
	for (int i = 0; i < p1Ships.size(); i++)
	{
		GBHPsum += p1Ships[i].getHealth();
	}
	for (int i = 0; i < p2Ships.size(); i++)
	{
		AIHPsum += p2Ships[i].getHealth();
	}
	if (GBHPsum <= 0)
	{
		return -1;
	}
	if (AIHPsum <= 0)
	{
		return 1;
	}
	return 0;
}
// the main function used to put ships on a board for an AI opponent
void Player::placeAIShips(vector<Ship> listOfShips)
{
	for (int j = 0; j < listOfShips.size(); j++) {
		vector<Coord> occupiedSpaces = calcAllOccupiedSpaces(listOfShips);
		for (int i = 0; i < occupiedSpaces.size(); i++)
		{
			if (i + 1 > listOfShips[j].getLength() && j + 1 < listOfShips.size())
			{
				j++;
			}
			if (_gameState[occupiedSpaces[i].getX()][occupiedSpaces[i].getY()] == '~')
			{
				_gameState[occupiedSpaces[i].getX()][occupiedSpaces[i].getY()] = listOfShips[j].getType()[0];
			}
		}
	}
}
void Player::addAtPos(Coord position, char thing)
{
	_gameState[position.getX()][position.getY()] = thing;
}
vector<string> Player::getGameState()
{
	return _gameState;
}
void Player::addHit(Coord pos)
{
	_GBHits.push_back(pos);
}
void Player::addMiss(Coord pos)
{
	_GBMisses.push_back(pos);
}
//AddPLayerShell
//INPUTS: Pos (Coord), allShips(vector<Ship>&)
//OUTPUTS: Bool
// Depends on: calcAllOccupiedSpaces()
// Automatically determines if a shell is a hit or miss, and puts it in the respective list
int Player::checkHit(Coord Pos, vector<Ship>& allShips)
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

		//_GBHits.push_back(Pos);
		return index;

	}

		//_GBMisses.push_back(Pos);


	
	return index;

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
//for(int i = 0; i < allShips.size(); i++)
	//{
		// I leave this here, because It's a good showing of my thinking, and figuing out an improvement
		// if (allShips[i].hitCheck(shell.getX(), shell.getY()) && coordIsUnique(shell))
		//{ 
		//	allShips[i].hit(shell.getX(), shell.getY());
		//	cout << "Hit!" << endl;
		//	checkHit(shell,allShips);
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
		//	checkHit(shell, allShips);
		//	return -1;
		//}
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
	int index = checkHit(shell, allShips);
		if(coordIsUnique(shell) && shell.getValid())
		{
			if (index >= 0 ) 
			{
				for (int j = 0; j < allShips.size(); j++)
				{
					vector<Coord> Temp = allShips[j].getOccupiedCoords();
					if (find(Temp.begin(), Temp.end(), shell) != Temp.end())
					{
						allShips[j].hit(shell.getX(), shell.getY());
						break;
					}
				}
				cout << "Hit!" << endl;
				_GBHits.push_back(shell);
				return 1;
			}
			else
			{
				std::cout << "Miss!" << endl;
				_GBMisses.push_back(shell);
				return -1;
			}
		}
		else
		{
			cout << "Looks like you tried to enter a duplicate coordinate. try again!" << endl;
			Player::PlayerShellUI(allShips,GBID);
			return 0;
		}
	
	
}
vector<Ship> Player::decodePassword(string password)
{
	vector<Ship> decodedShips;
	string CoordDecoding;
	for (int i = 0; i < password.size(); i += 4)
	{

		CoordDecoding = string(1, password[i + 1]) + password[i + 2];
		Coord decodedCoord = Coord(CoordDecoding);
		if (Ship::isValidType(string(1, password[i]))) {
			decodedShips.push_back(Ship(string(1, password[i]), decodedCoord.getX(), decodedCoord.getY(), password[i + 3] == 'X'));
		}
		else
		{
			return { Ship("Error", -1,-1, false) };
		}
	}
	return decodedShips;
}
string Player::encodePassword(vector<Ship> Ships)
{
	string output;
	for (int i = 0; i < Ships.size(); i++)
	{
		output += Ships[i].getType();
		Coord shipPos = Coord(Ships[i].getXpos(), Ships[i].getYpos());
		output += Coord::getPosUI(shipPos.getX(), shipPos.getY(), shipPos);
		if (Ships[i].getFacing())
		{
			output += 'X';
		}
		else
		{
			output += 'Y';
		}

	}
	return output;
}
vector<Ship> Player::handlePassword()
{
	string password;
	bool isEnteringPassword = true;
	vector<Ship> allShips;
	while (isEnteringPassword) {
		cout << "A password allows you to save and load a previous board layout. type a password below to use one, then ENTER to confirm, OR just press ENTER to skip." << endl;
		cout << "if there are any spaces before, after or anywhere in the password, make sure to remove them before continuing" << endl;
		allShips = {};

		getline(cin, password);
		if (password.size() > 2)
		{
			allShips = decodePassword(password);
			if (Ship::validateShips(allShips))
			{
				cout << "Password validated successfully!" << endl;
				return allShips;
			}
			else
			{
				cout << "Bad Password!" << endl;
				continue;
			}
		}
		else
		{

			isEnteringPassword = false;
		}



	}
	return allShips;
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
		this->placeAIShips(allShips);
		this->displayBoard({"Null"});
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
		
		
		
		//P2DYS5EXCF8YA5IX
		// TEST LAYOUT: Patrol: D2 |, Submarine: E5 -, Cruiser: F8 | Battleship: D5 | cArrier: I5 -
		// use the above for testing
	}
	// reset the player's view of their own board, so that main can write the state.
	_gameState = { "~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~" };
	return allShips;
}
void Player::displayBoard(vector<string> gameStateInstance = {"Null"})
{
	cout << "  ABCDEFGHIJ" << endl;
	const string Xref = "0123456789";
	string out = "";
	for (int i = 0; i < Xref.size(); i++)
	{
		out = "";
		out += Xref[i];
		out += " ";
		if(gameStateInstance != vector<string>{"Null"})
		{
			out += gameStateInstance[i];
		}
		else 
		{
			out += _gameState[i];
		}
		cout << out << endl;
	}
}