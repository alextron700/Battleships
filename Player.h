#pragma once
#include <vector>
#include "Coord.h"
#include "Ship.h"
#include "string"
#include <iostream>
//Player should have Player I/O
//Next: Move the four board methods over to player, and take _gamestate with it
using namespace std;
class Player
{
public:
	Player();
	int  checkHit(Coord pos, vector<Ship>& allShips);
	vector<Coord> getPlayerHits();
	vector<Coord> getPlayerMisses();
	void addHit(Coord pos);
	void addMiss(Coord pos);
	static vector<Coord> calcAllOccupiedSpaces(vector<Ship>& allShips);
	void drawHits();
	int PlayerShellUI(vector<Ship>& allShips, string GBID);
	bool coordIsUnique(Coord input);
	vector<Ship> GBUI();
	static string encodePassword(vector<Ship> ships);
	static vector<Ship> decodePassword(string password);
	static vector<Ship> handlePassword();
	void displayBoard(vector<string> gameStateInstance);
	vector<string> getGameState();
	void addAtPos(Coord pos, char thing);
	void placeAIShips(vector<Ship> listOfShips);
	static int determineWin(vector<Ship> p1Ships, vector<Ship> p2Ships);
private:
	vector<Coord> _GBHits; // hits the GB made
	vector<Coord> _GBMisses;
	vector<string> _HitDiagram;
	vector<string> _gameState;
};

