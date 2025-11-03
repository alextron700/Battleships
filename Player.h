#pragma once
#include <vector>
#include "Coord.h"
#include "Ship.h"
#include "string"
#include <iostream>
//Player should have Player I/O
//Next: Move the four board methods over to player, and take _gamestate with it
using namespace std;
class Opponent;
class Player
{
public:
	Player(vector<Ship> allShips);
	int  checkHit(Coord pos, vector<Ship>& allShips);
	vector<Coord> getPlayerHits();
	vector<Coord> getPlayerMisses();
	void addHit(Coord pos);
	void addMiss(Coord pos);
	static vector<Coord> calcAllOccupiedSpaces(vector<Ship>& allShips);
	void drawHits();
	bool PlayerShellUI(vector<Ship>& allShips, string playerID, Opponent* p);
	bool coordIsUnique(Coord input);
	vector<Ship> playerUI();
	string encodePassword();
	static vector<Ship> decodePassword(string password);
	static vector<Ship> handlePassword();
	void displayBoard(vector<string> gameStateInstance);
	vector<string> getOwnShipView();
	void addAtPos(Coord pos, char thing);
	void placeShips(vector<Ship> listOfShips);
	int setAllShips(vector<Ship>* ships);
	static int determineWin(vector<Ship>& p1Ships, vector<Ship>& p2Ships);
	vector<Ship>& getAllShips();
	vector<Coord>getAllOccupiedSpaces();
	void handleShips(vector<Ship>& allShips, Player* opponent);
	vector<string> getEnemyShipView();
	bool setupPlayer(vector<Ship>& allShips);
	void initialiseOpponent();
	virtual bool TakeTurn(string PlayerID, Opponent* o);
	static void turnLoop(Player* POne, Opponent* o);
private:
	vector<Coord> _playerHits; //Hits this instance of player made
	vector<Coord> _playerMisses; //Misses this instance of player made
	vector<string> _enemyShipView;
	vector<string> _ownShipView;
	vector<Ship> _allShips;
	vector<Coord> _allOccupiedSpaces;
};

