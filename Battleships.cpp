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
using namespace std;
// the system is supposed to be simple. 
vector<Ship> decodePassword(string password)
{
	vector<Ship> decodedShips;
	string CoordDecoding;
	for (int i = 0; i < password.size(); i+=4) 
	{
	
		CoordDecoding = string(1,password[i+1]) + password[i+2];
		Coord decodedCoord = Coord(CoordDecoding);
		if (Ship::isValidType(string(1, password[i]))) {
			decodedShips.push_back(Ship(string(1, password[i]), decodedCoord.getX(), decodedCoord.getY(), password[i + 3] == 'X'));
		}
		else
		{
			return { Ship("Error", -1,-1, false) };
		}
	}
	return decodedShips;
}
string encodePassword(vector<Ship> Ships)
{
	string output;
	for (int i = 0; i < Ships.size(); i++)
	{
		output += Ships[i].getType();
		Coord shipPos = Coord(Ships[i].getXpos(), Ships[i].getYpos());
		output += shipPos.getPosUI(shipPos.getX(), shipPos.getY());
		if (Ships[i].getFacing())
		{
			output += 'X';
		}else
		{
			output += 'Y';
		}
		
	}
	return output;
}
vector<Ship> handlePassword()
{
	string password;
	bool isEnteringPassword = true;
	vector<Ship> allShips;
	while (isEnteringPassword) {
		cout << "A password allows you to save and load a previous board layout. type a password below to use one, then ENTER to confirm, OR just press ENTER to skip." << endl;
		cout << "if there are any spaces before, after or anywhere in the password, make sure to remove them before continuing" << endl;
		allShips = {};

		getline(cin, password);
		if (password.size() > 2)
		{
			allShips = decodePassword(password);
			if (Ship::validateShips(allShips))
			{
				cout << "Password validated successfully!" << endl;
				return allShips;
			}
			else
			{
				cout << "Bad Password!" << endl;
				continue;
			}
		}
		else
		{

			isEnteringPassword = false;
		}



	}
	return allShips;
}
int main()
{
	std::cout << "Welcome to Battleships." << endl;
	
	vector<Ship>allShips = {};
	
	string savedPassword;
	
	GameBoard player = GameBoard(allShips, "Player");
	allShips = handlePassword();
	if (!allShips.size() > 0) 
	{
		allShips = player.playerUI();
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
		string EP = encodePassword(allShips);
		cout << "Your password is: " << EP << endl;
	}
	player.prepareDisplayBoard(true);
	player.addShips(allShips);
	//player.displayBoard();
	for (int i = 0; i<player.getAllShips().size(); i++)
	{
		cout << player.getAllShips()[i].getType();
	}
	player.displayBoard();
	// Logic needed: AI, win/loss detect, turn system.
	// Initialise Opponent
	vector<Ship> AIShips = {};
	const vector<string> potentialPositions = {
	"A4GYB6HXC4CYP5DXS5JY",
	"A0EXB5FYC4IYS6CXP8DY",
	"A0EXB1EXC2EXS3EXP4EX",
	"A1EXB6CYS3GXP7DXC7GY",
	"B3FXC6GYS2DXA9EXP1EY",
	"A1EXB2EXC3EXS4EXP5EX",
	"P2DYS4FYC9JXB6HXA7FX",
	"P2DYS6FXA4IYB7GXC4BY"
	};
	AIShips = decodePassword(potentialPositions[rand() % potentialPositions.size()]);
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
