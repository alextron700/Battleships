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
	
	_boardID = boardID;
	_GB = Player();
	_allOccupiedSpaces = Player::calcAllOccupiedSpaces(allShips);
}
// these getPlayerHitIndex and getPlayerMissIndex are designed for an iterator to display a list
// if an error occurs, you get the error coordinate
string GameBoard::getBoardID() 
{
	return _boardID;
}

// getAIhits and getAIMisses return the whole list, since the AI is likely to need the whole list.

vector<Coord> GameBoard::getAllOccupiedSpaces() 
{
	return _allOccupiedSpaces;
}
//addPlayerShell() 
//INPUTS: Pos (Coord), allShips(vector<Ship>&)
//OUTPUTS: None (none)
//Depends on: Coord class, ship class, getAllOccupiedSpaces
//This automatically does hit checking, adding it to a list as appropriate

// note: Depends on AddPlayerShell()
void GameBoard::prepareDisplayBoard(Player* opponent)
{	
	if(opponent == NULL)
	{
		return;
	}
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

		// this requires repetition. We are indexing through lists of differing sizes.
		for(int i = 0; i < opponent->getPlayerMisses().size(); i++)
		{
			_gameState[opponent->getPlayerMisses()[i].getX()][opponent->getPlayerMisses()[i].getY()] = "X";
		}
		for (int i = 0; i < opponent->getPlayerHits().size(); i++)
		{
			_gameState[opponent->getPlayerHits()[i].getX()][opponent->getPlayerHits()[i].getY()] = "h";
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
		hitList = _GB.getPlayerHits();
	
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


void GameBoard::drawBoard(vector<Ship>& allShips, GameBoard& g, Player* opponent)
{
	g.prepareDisplayBoard(opponent);
	g.addShips(allShips);
	g.displayBoard();

}