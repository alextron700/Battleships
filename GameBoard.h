#pragma once
#include <string>
#include <vector>
#include "Coord.h"
#include "Ship.h"
#include <set>
#include <map>
using namespace std;
class GameBoard
{
public:
	GameBoard(vector<Ship>& allShips, string boardID);
	void prepareDisplayBoard(bool playerBoard);
	void addShips(vector<Ship>& allShips);
	void displayBoard();
	Coord getPlayerHitIndex(int index);
	Coord getPlayerMissIndex(int index);
	bool  AddPlayerShell(Coord pos, vector<Ship>& allShips);
	vector<Coord> calcAllOccupiedSpaces(vector<Ship>& allShips);
	vector<Coord> getAllOccupiedSpaces();
	string getBoardID();
	vector<Ship> playerUI();
	vector<Ship> getAllShips();
private:
	vector<Ship> _allShips;
	string _boardID;
	vector<Coord> _allOccupiedSpaces;
	vector<vector<string>> _gameState;
	vector<Coord> _playerHits; // hits the player made
	vector<Coord> _playerMisses;
};

