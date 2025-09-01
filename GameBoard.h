#pragma once
#include <string>
#include <vector>
#include "Coord.h"
#include "Ship.h"
#include "Player.h"
#include <set>
#include <map>
using namespace std;
class GameBoard
{
public:
	GameBoard(vector<Ship>& allShips, string boardID);
	void prepareDisplayBoard(Player* opponent);
	void addShips(vector<Ship>& allShips);
	void displayBoard();
	static void drawBoard(vector<Ship>& allShips, GameBoard& g, Player* opponent = NULL);
	vector<Coord> getAllOccupiedSpaces();
	string getBoardID();
	
	vector<Ship> getAllShips();
private:
	vector<Ship> _allShips;
	string _boardID;
	vector<Coord> _allOccupiedSpaces;
	vector<vector<string>> _gameState;
	Player _GB;
};

