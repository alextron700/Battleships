#include "Opponent.h"
#include <iostream>
#include <string>
#include "GameBoard.h"
#include "Coord.h"
#include <algorithm>

//enum AIModes
//{
//	smart = 0x01,
//	hook = 0x02,
//	cheat = 0x04
//};
Opponent::Opponent(vector<Ship>& AIShips)
	:Player(AIShips), _lastSSCoord(0, 0)
{
	
	_doSmartSearch = false;
	_doHook = false;
	_cheatsAllowed = false;
	_hasHook = false;
	_SSIndex = 0;
	_smartCheatIndex = 0;
	_smartSearchPattern = {
		"00~~~~~~~3",
		"~~0~~~~~3~",
		"~~~0~~~3~~",
		"~~~~0~3~~~",
		"~~~~~4~~~~",
		"~~~~21~~~~",
		"~~~2~~1~~~",
		"~~2~~~~1~~",
		"~2~~~~~~1~",
		"2~~~~~~~~1"
	};
	_smartSearchOffsets = { Direction(1,0),Direction(-1,0),Direction(0,1),Direction(0,-1),Direction(-4,-5)};
	_lastSSCoord = Coord(0, 0);
	srand(time(0));
}
// this is the player's difficulty settings for the opponent.
/*
setUpOpponent();
inputs: none
outputs: none
depends on: Opponent();
This initialises the settings for the Opponent.
*/
void Opponent::setUpOpponent()
{
	string difficulty;
	bool tryAgain = true;
	cout << "Pick a difficulty. This will be a whole number between 0 and 7.\n 0 is the easiest. \n 7 is the hardest." << endl;
	
	// this if block is here, because it serves two important roles, both setting the appropriate values, AND 
	// validating user input. 
	// This can't be a switch statement either, I already tried that. a string is not an "integral type", which
	// a switch statement apparently needs
	while (tryAgain) {
		getline(cin, difficulty);
		char c = difficulty[0] - '0';
		tryAgain = false;
		if ((c & 0x01) != 0) // enables the methodical search pattern
		{
			_doSmartSearch = true;
		}
		if ((c & 0x02) != 0) // enables the "hook" strategy.
		{

			_doHook = true;
		}
		if ((c & 0x04) != 0) // enables cheating
		{
			_cheatsAllowed = true;
		}
		if (c < 0 || c > 7)
		{
			cout << difficulty << " is not a valid difficulty. \n Valid difficluties are a whole number, no less than 0, and no greater than 7, try again!" << endl;
			tryAgain = true;
		}

	}
}
/*
smartSearch()
INPUTS: NONE
OUTPUTS: _lastSSCoord
DEPENDS ON: TakeTurn()
Returns the next item in a pre-set sequence of coordinates,
calculating the next item in the sequence by using an overloaded +
and a series of offsets.
*/
Coord Opponent::smartSearch()
{
	
	char SSCheck = _smartSearchPattern[_lastSSCoord.getX()][_lastSSCoord.getY()];
	
	switch (SSCheck)
	{
	case '0':
		_SSIndex = 0;
		break;
	case '1':
		_SSIndex = 1;
		break;
	case '2':
		_SSIndex = 2;
		break;
	case '3':
		_SSIndex = 3;
		break;
	case '4':
		_SSIndex = 4;
		break;
	}

	
	_lastSSCoord = Coord(_lastSSCoord.getX() + _smartSearchOffsets[_SSIndex].x,_lastSSCoord.getY() + _smartSearchOffsets[_SSIndex].y);
	return _lastSSCoord;
}
/*
* INPUTS: allShips (Vector<Ship>&), PlayerID (String), p (Player*)
* OUTPUTS: retVal (Coord)
* DEPENDS ON: NONE
This is the primary function to call upon AI turn.
*/
Coord Opponent::TakeTurn(string PlayerID, Player* p)
{
	handleShips(this->getAllShips(),p);
	int AIRand = rand() % 101;
	vector<Coord> targets = p->getAllOccupiedSpaces();
	Coord retVal = Coord(0, 0);
	if (_cheatsAllowed && AIRand >= 25 && !_doSmartSearch)
	{
		Coord TPos = targets[rand() % targets.size()];
		int Yoffset = rand()%7; // the formula should be Abs(max)+Abs(min) + 1
		if(Yoffset >= 3)
		{
			Yoffset -= (Yoffset - 3);
			Yoffset = -Yoffset;
		}
		int Xoffset = rand() % 7;
		if (Xoffset >= 3)
		{
			Xoffset -= (Xoffset - 3);
			Xoffset = -Xoffset;
		}
		Coord shellLoc = Coord(TPos.getX() + Xoffset, TPos.getY() + Yoffset);
		if (shellLoc.getValid())
		{
		 retVal = shellLoc;
		}

	}if (_cheatsAllowed && AIRand >= 25 && _doSmartSearch)
	{
		if (_smartCheatIndex + 1< targets.size())
		{
			//_smartCheatIndex++;
			retVal = targets[_smartCheatIndex++];
			goto handleShot;
		}
	}
	if (!_doSmartSearch && ! _hasHook)
	{
		retVal = Coord(rand() % 10, rand() % 10);
	} else
	{
		retVal = smartSearch() + retVal;
	}
	if ((AddPlayerShell(retVal, p->getAllShips()) != -1 && _doHook) || _hasHook)
	{
		retVal = Hook(p->getAllShips(), *(p), retVal);
	}
	handleShot:
	if (AddPlayerShell(retVal, p->getAllShips()) != -1)
	{
		addHit(retVal);
	}
	else {
		addMiss(retVal);
	}
	std::cout <<"the Computer is aiming at: "<< Coord::getPosUI(retVal.getX(), retVal.getY()) << endl;
	return retVal;
}
// I felt that the AI's "Hook" strategy should get it's own function, given it's complex nature.
Coord Opponent::Hook(vector<Ship> AllShips, Player pInstance, Coord Pos)
{
	if (_HookedShip.getType() != "Error" && Pos == Coord(-1, -1))
	{
		Pos = _HookedShip.getOccupiedCoords()[_HookIndex];
	}
	int PShipIndex = pInstance.AddPlayerShell(Pos, AllShips);
	
	if(PShipIndex != -1 && _hasHook == false)
	{
		for (int i = 0; i < AllShips.size(); i++)
		{
			if(AllShips[i].hitCheck(Pos.getX(),Pos.getY()))
			{
				vector<Coord> occupiedSpaces = AllShips[i].getOccupiedCoords();
				_HookedShip = AllShips[i];
				_HookIndex = find(occupiedSpaces.begin(), occupiedSpaces.end(), Pos) - occupiedSpaces.begin();
				_hasHook = true;
			}
			
		}
	}
	if (_hasHook &&_HookedShip.getType() != "Error" && _HookedShip.getHealth() != 0)
	{
		_HookIndex = (_HookIndex + 1) % (_HookedShip.getLength());
		if (_HookIndex + 1 == _HookedShip.getLength())
		{
			_HookIndex = 0;
			_hasHook = false;
		}
	}
	if (_HookedShip.getType() != "Error")
	{
		return _HookedShip.getOccupiedCoords()[_HookIndex];
	}
	return Coord(9, 9); // return something, since this function needs something valid to return
}
