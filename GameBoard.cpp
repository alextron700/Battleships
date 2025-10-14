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
void GameBoard::drawPlayerData(Player data, Player* opponent)
{
	data.drawHits();
	vector<Ship> AllShips = data.getAllShips();
	data.handleShips(AllShips, opponent);
	data.displayBoard({"Null"});
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

	bool hitclr = false;
	bool unhitclr = false;
	bool xclr = false;
	bool oclr = false;
	//bool declr = false;
	input.insert(0, "\033[0;37;44m");
	input.insert(input.size(), "\033[0m");
	for (int i = 0; i < input.size(); i++)
	{
		switch (input[i])
		{
		//case '~':
		//	if (hitclr or unhitclr or oclr or xclr)
		//	{
		//		input.insert(i, "\033[0;37;44m");
		//		//declr = true;
		//		unhitclr = false;
		//		hitclr = false;
		//		xclr = false;
		//		oclr = false;
		//		continue;

        //   }
		case 'X':
			if (!xclr)
			{
				input.insert(i, "\033[0;31;44m");
				xclr = true;
				oclr = false;
				unhitclr = false;
				hitclr = false;
				//declr = false;
				continue;
			}
			break;
		case 'O':
			if (!oclr)
			{
				input.insert(i, "\033[0;37;44m");
				oclr = true;
				xclr = false;
				unhitclr = false;
				hitclr = false;
				//declr = false;
				continue;
			}
			break;
		case 'P':
		case 'S':
		case 'C':
		case 'B':
		case 'A':
			if (!unhitclr)
			{
				input.insert(i, "\033[0;90;44m");
				unhitclr = true;
				hitclr = false;
				oclr = false;
				xclr = false;
				//declr = false;
			}
			break;
		case 'p':
		case 's':
		case 'c':
		case 'b':
		case 'a':
			if (!hitclr)
			{
				input.insert(i, "\033[1;4;5;7;91;40m");
				hitclr = true;
				unhitclr = false;
				oclr = false;
				xclr = false;
				//declr = false;
				continue;
			}
			break;
		}
	}
	return input;
}

