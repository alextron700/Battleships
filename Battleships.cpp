// Battleships.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Ship.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include "Coord.h"
#include "GameBoard.h"
#include "Player.h"
#include <ctime>
using namespace std;
void renderBoard(Player* instance,vector<Ship> allShips, GameBoard& GB, Player* opponent = NULL)
{
	GameBoard::drawBoard(allShips, GB,opponent);
	instance->displayBoard(GB.getLocalGameState());
}
int main()
{
	std::cout << "Welcome to Battleships." << endl;
	
	vector<Ship>allShips = {};
	
	string savedPassword;
	
	GameBoard GB = GameBoard(allShips, "Player");
	allShips = Player::handlePassword();
	Player POne = Player();
	renderBoard(&POne, allShips,GB,NULL);
	if (allShips.size() <= 0) 
	{
		allShips = POne.GBUI();
	}
	if (allShips[0].getType() == "Error")
	{
		cout << "It looks like an error happened!" << endl;
		return -1;
	}
	cout << "would you like to save your setup? (Enter == No | Any key, then Enter == Yes)." << endl;
	getline(cin, savedPassword);
	if (savedPassword.size() > 0)
	{
		string EP = Player::encodePassword(allShips);
		cout << "Your password is: " << EP << endl;
	}

	vector<Ship> AIShips = {};
	const vector<string> potentialPositions = {
	"A4GYB6HXC4CYP5DXS5JY",
	"A0EXB5FYC4IYS6CXP8DY",
	"A0EXB1EXC2EXS3EXP4EX",
	"A1EXB6CYS3GXP7DXC7GY",
	"B3FXC6GYS2DXA9EXP1EY",
	"A1EXB2EXC3EXS4EXP5EX",
	"P2DYS4FYC9JXB6HXA7FX",
	"P2DYS6FXA4IYB7GXC4BY",
	"P2DXS5EYC8FXB5DXA5IY"
	};
	srand(time(0));
	AIShips = Player::decodePassword(potentialPositions[rand() % potentialPositions.size()]);
	Player PTwo = Player();
	GameBoard AIGB = GameBoard(AIShips, "AI");
	bool GBTurn = true; 
	
	while (true) {
		if(Player::determineWin(allShips,AIShips) == -1)
		{
			cout << "AI Win!";
			return 0;
		}
		if (Player::determineWin(allShips, AIShips) == 1)
		{
			cout << "Human Win!";
			return 0;
		}
		if (GBTurn)
		{
			renderBoard(&POne, allShips, GB, &PTwo);
			POne.PlayerShellUI(AIShips, "Player");
			GBTurn = false;
		}
		else
		{
			//AI's move.

			Coord AIShot = Coord(rand() % 10, rand() % 10);
			cout << Coord::getPosUI(AIShot.getX(), AIShot.getY(), AIShot) << endl;
			if(PTwo.checkHit(AIShot, allShips) != -1)
			{
				PTwo.addHit(AIShot);
			}else
			{
				PTwo.addMiss(AIShot);
			}
			GBTurn = true;

		}
	
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
