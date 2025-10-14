// Battleships.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Ship.h"
#include <string>
#include <vector>
#include <algorithm>
#include "Coord.h"
#include "GameBoard.h"
#include "Player.h"
#include <ctime>
#include "Opponent.h"
using namespace std;

// Password: all ships bottom right: A9JYB9IYC9HYS9FYP9GY

const char* ansi_red = "\033[1;31m";
const char* ansi_clear = "\033[0m";

int main()
{
	std::cout << ansi_red << "Welcome to Battleships." << ansi_clear << endl;
	// initialise palyer variables
	vector<Ship>allShips = {};
	string savedPassword;
	Player POne = Player(allShips); // set up a player with an empty ship array
	allShips = Player::handlePassword(); // attempt to populate with a password
	POne.setupPlayer(allShips); // manual setup
	if (POne.getPlayerMisses().size() > 0) 
	{
		if (POne.getPlayerMisses()[0] == Coord(-1, -1))
		{
			cout << "Oh no, a fatal error happened! x_x" << endl;
			return -1;
		}
	}
		cout << "would you like to save your setup? (Enter == No | Any key, then Enter == Yes)." << endl;
		getline(cin, savedPassword);
	//P1AYS2BYC2CYB3DYA4EY
	//POne.setAllShips(allShips);
	GameBoard::drawPlayerData(POne,NULL);
	if (savedPassword.size() > 0)
	{
		string EP = POne.encodePassword();
		cout << "Your password is: " << EP << endl;
	}
	// Set up the AI opponent
	vector<Ship> AIShips;
	Opponent AI = Opponent(AIShips);
	AI.setUpOpponent();
	AI.initialiseOpponent();
	AI.handleShips(AIShips,&AI);
	//AI.setAllShips(AIShips);
	Player::turnLoop(&POne, &AI); // the main game
	
	
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
