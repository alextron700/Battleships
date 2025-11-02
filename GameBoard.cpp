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
// INPUTS: gameState (vector<string>)
// OUTPUTS: None (None)
// Depends on: None
// initialises game board
GameBoard::GameBoard(vector<string> gameState) 
{
	_state = gameState;
}
/*
drawPlayerData
Inputs: data (Player), opponent (Player*)
Outputs: None (Null)
Depends on: None()
Decodes player data into a graphic. 
*/
void GameBoard::drawPlayerData(Player* data, Player* opponent)
{
	
	data->drawHits();
	vector<Ship> AllShips = data->getAllShips();
	data->handleShips(AllShips, opponent);
	data->displayBoard({"Null"});
}
void GameBoard::updateState(Player instanceToUpdate, Coord Position, char newStuff)
{
	instanceToUpdate.addAtPos(Position, newStuff);
	_state[Position.getX()][Position.getY()] = newStuff;
}
/*
* drawState()
INPUTS: addPosReference (bool)
OUTPUTS: None
DEPENDS ON: None
Draws whatever is in the state variable. if it is passed true,
A reference for rows and columns as well.
NOTE: This function assumes a 10 x 10 board or smaller. 
A bigger board may lead to the Yref not quite fitting, and garbage values on the Xref
*/
void GameBoard::drawState(bool addPosReference = true)
{
	if (addPosReference)
	{
		cout << "ABCDEFGHIJ" << endl;
	}
	 string output;
	for (int i = 0; i < _state.size(); i++)
	{
		if (addPosReference)
		{
			output += i + '0';
		}
		output += _state[i];
		cout << output << endl;
	}
}
/*
drawRawData()
Inputs: rawData
Outputs: none
Draws whatever it is given. Use with caution.
*/
void GameBoard::drawRawData(vector<string> rawData)
{
	if (rawData.size() <= 0)
	{
		return;
	}
	for (int i = 0; i < rawData.size(); i++)
	{
		cout << rawData[i] << endl;
	}
}

/*
Inputs: allShips (vector<Ship>&)
Outputs (Bool)
Depends on: getOccupiedCoords()
Checks if two or more ships occupy the same space
*/
string GameBoard:: colorise(string input)
{

	const string XColor = "\033[0;31;44m";
	const string OColor = "\033[0;37;44m";
	const string unhitColor = "\033[0;90;4m";
	const string hitColor = "\033[1;4;5;7;91;40m";
	input.insert(0, "\033[0;37;44m");
	int i = 0;
	bool advance = true;
	while (i < input.size())
	{
		advance = true;
		switch (input[i])
		{
			
		case 'X':

				input.insert(i, "\033[0;31;44m");
				input.insert((i+XColor.size())+1, "\033[0;37;44m");
				i += XColor.size() + OColor.size() + 1;
				advance = false;

			break;
		case 'O':
			
				input.insert(i, "\033[0;37;44m");
				input.insert((i+OColor.size())+1, "\033[0;37;44m");
				i += OColor.size() + OColor.size() + 1;
				advance = false;
			
			break;
		case 'P':
		case 'S':
		case 'C':
		case 'B':
		case 'A':

				input.insert(i, "\033[0;90;44m");
				input.insert((i+unhitColor.size())+2, "\033[0;37;44m");
				advance = false;
				i += unhitColor.size() +OColor.size() + 1;
			
			break;
		case 'p':
		case 's':
		case 'c':
		case 'b':
		case 'a':
				input.insert(i, "\033[1;4;5;7;91;40m");
				input.insert((i+hitColor.size())+1, "\033[0;37;44m");
				advance = false;
				i += hitColor.size() + OColor.size() + 1;
			
			break;
		}
		if (advance)
		{
			i++;
		}
		
	}
	input.insert(input.size(), "\033[0m");
	return input;
}

