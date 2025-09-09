#pragma once
#include <string>
#include <vector>
#include "Coord.h"
#include "Ship.h"
#include "Player.h"
#include <set>
#include <map>
using namespace std;
//GameBoard handles internal state information that the player doesn't see
// Next: Move prepareDisplayBoard, addShips, displayBoard, and _gameState to the Player class
class GameBoard
{
public:
	GameBoard(vector<Ship>& allShips, string boardID);
	void prepareDisplayBoard(Player* opponent);
	void addShips(vector<Ship>& allShips);
	static bool drawBoard(vector<Ship>& allShips, GameBoard& g, Player* opponent = NULL);
	vector<Coord> getAllOccupiedSpaces();
	string getBoardID();
	int setAllShips(vector<Ship> ships);
	vector<string> getLocalGameState();
	vector<Ship> getAllShips();
private:
	vector<Ship> _allShips;
	string _boardID;
	Player _GB;
	vector<Coord>_allOccupiedSpaces;
};

