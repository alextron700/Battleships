#pragma once
#include <vector>
#include "Coord.h"
#include "Ship.h"
#include "string"
#include <iostream>
using namespace std;
class Player
{
public:
	Player();
	bool  AddPlayerShell(Coord pos, vector<Ship>& allShips);
	vector<Coord> getPlayerHits();
	vector<Coord> getPlayerMisses();
	static vector<Coord> calcAllOccupiedSpaces(vector<Ship>& allShips);
	void drawHits();
	int PlayerShellUI(vector<Ship>& allShips, string GBID);
	bool coordIsUnique(Coord input);
	vector<Ship> GBUI();
private:
	vector<Coord> _GBHits; // hits the GB made
	vector<Coord> _GBMisses;
	vector<string> _HitDiagram;
};

