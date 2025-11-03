#include "Player.h"
#include <string>
#include <iostream>
#include "GameBoard.h"
#include "Opponent.h"
using namespace std;
Player::Player(vector<Ship> allShips)
{
	_playerHits = {};
	_playerMisses = {};
	_enemyShipView = {
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~"
	};
	_ownShipView = {
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~",
		"~~~~~~~~~~"
	};
	_allShips = allShips;
	_allOccupiedSpaces = Player::calcAllOccupiedSpaces(allShips);
}
//CalcAllOccupiedSpaces
//INPUTS: allShips (vector<Ship>&)
//OUTPUTS: OccupiedSpaces (vector<Coord>)
//Depends on: Ship:getOccupiedCoords
// Calculates all the spaces occupied by the given list of ships
vector<Coord> Player::calcAllOccupiedSpaces(vector<Ship>& allShips)
{

	vector<Coord> OccupiedSpaces = {};
	// this takes all the spaces occupied by ships into a vector
	for (int i = 0; i < allShips.size(); i++)
	{
		vector<Coord> Occu = allShips[i].getOccupiedCoords();
		for (int j = 0; j < Occu.size(); j++) {
			OccupiedSpaces.push_back(Occu[j]);
		}
	}
	return OccupiedSpaces;
}
vector<Coord> Player::getAllOccupiedSpaces()
{
	return _allOccupiedSpaces;
}
// determines which side has won, if a win is even detected
int Player::determineWin(vector<Ship>& p1Ships, vector<Ship>& p2Ships)
{
	int playerHPsum = 0;
	int AIHPsum = 0;
	for (int i = 0; i < p1Ships.size(); i++)
	{
		playerHPsum += p1Ships[i].getHealth();
	}
	for (int i = 0; i < p2Ships.size(); i++)
	{
		AIHPsum += p2Ships[i].getHealth();
	}
	if (playerHPsum <= 0)
	{
		return -1;
	}
	if (AIHPsum <= 0)
	{
		return 1;
	}
	return 0;
}
// the main function used to put ships on a board for an AI opponent
void Player::placeShips(vector<Ship> listOfShips)
{
	vector<Coord> occupiedSpaces = calcAllOccupiedSpaces(listOfShips);
	for (int j = 0; j < listOfShips.size(); j++) {
		
		for (int i = 0; i < occupiedSpaces.size(); i++)
		{
			if (i + 1 > listOfShips[j].getLength() && j + 1 < listOfShips.size())
			{
				j++;
			}
			if (_ownShipView[occupiedSpaces[i].getX()][occupiedSpaces[i].getY()] == '~')
			{
				_ownShipView[occupiedSpaces[i].getX()][occupiedSpaces[i].getY()] = listOfShips[j].getType()[0];
			}
		}

	}
	_allOccupiedSpaces = occupiedSpaces;
}
void Player::addAtPos(Coord position, char thing)
{
	_ownShipView[position.getX()][position.getY()] = thing;
}
vector<string> Player::getOwnShipView()
{
	return _ownShipView;
}
vector<string> Player::getEnemyShipView()
{
	return _enemyShipView;
}
void Player::addHit(Coord pos)
{
	_playerHits.push_back(pos);
}
void Player::addMiss(Coord pos)
{
	_playerMisses.push_back(pos);
}
//AddPLayerShell
//INPUTS: Pos (Coord), allShips(vector<Ship>&)
//OUTPUTS: Bool
// Depends on: calcAllOccupiedSpaces()
// Automatically determines if a shell is a hit or miss, and puts it in the respective list
int Player::AddPlayerShell(Coord Pos, vector<Ship>& allShips)
{
	int index = -1;
	vector<Coord> OccupiedSpaces = calcAllOccupiedSpaces(allShips);
	for (int i = 0; i < OccupiedSpaces.size(); i++)
	{
		if (OccupiedSpaces[i] == Pos)
		{
			index = i;
			break;
		}
	}
	_allOccupiedSpaces = OccupiedSpaces;
	if (index >= 0)
	{

		//_playerHits.push_back(Pos);
		return index;

	}

		//_playerMisses.push_back(Pos);


	
	return index;

}
// getPlayerHits and getPlayerMisses
// INPUTS: NONE
// OUTPUTS:
// GetPlayerMisses: _playerMisses (vector<Coord>)
// GetPlayerHits: _playerHits (vector<Coord>)
// Depends on: None
// returns their respective lists
vector<Coord> Player::getPlayerHits()
{
	return _playerHits;
}
vector<Coord> Player::getPlayerMisses()
{
	return _playerMisses;
}
//drawHits
// INPUTS: None(None)
// OUTPUTS: None(None)
// Depends on: None
// Draws the diagram for the palyer to see their hits and misses
void Player::drawHits()
{


	for (int i = 0; i < _playerMisses.size(); i++)
	{
		_enemyShipView[_playerMisses[i].getX()][_playerMisses[i].getY()] = 'O';
	}
	for(int i = 0; i< _playerHits.size(); i++)
	{
		_enemyShipView[_playerHits[i].getX()][_playerHits[i].getY()] = 'X';
	}
	cout << " ABCDEFGHIJ" << endl;
	for (int i = 0; i < _enemyShipView[0].size(); i++)
	{
		cout << i << GameBoard::colorise(_enemyShipView[i])  << endl;
	}
}
int Player::setAllShips(vector<Ship>* ships)
{
	_allShips = *(ships);
	_allOccupiedSpaces = calcAllOccupiedSpaces(_allShips);
	return -1;
}

vector<Ship>& Player::getAllShips()
{
	return _allShips;
}
// Main Will have to call drawBoard() On it's own
bool Player::coordIsUnique(Coord input)
{
	return (find(_playerHits.begin(), _playerHits.end(), input) == _playerHits.end()) && (find(_playerMisses.begin(), _playerMisses.end(), input) == _playerMisses.end());
}
//for(int i = 0; i < allShips.size(); i++)
	//{
		// I leave this here, because It's a good showing of my thinking, and figuing out an improvement
		// if (allShips[i].hitCheck(shell.getX(), shell.getY()) && coordIsUnique(shell))
		//{ 
		//	allShips[i].hit(shell.getX(), shell.getY());
		//	cout << "Hit!" << endl;
		//	AddPlayerShell(shell,allShips);
		//	if(allShips[i].getHealth() == 0)
		//	{
		//		cout << "Sank Opponent's " << convertShipID.at(allShips[i].getType()) << "!" <<endl;
		//	}
		//	return 0;
		//}else if(!coordIsUnique(shell))
	//	{
		//	cout << "Looks like you tried to enter a duplicate coordinate. try again!" << endl;
		//Player::PlayerShellUI(allShips);
		//	return 0;
		//}
		//else
		//{
		//	cout << "Miss!" << endl;
		//	AddPlayerShell(shell, allShips);
		//	return -1;
		//}
 Coord Player::PlayerShellUI(vector<Ship>& allShips, string playerID = "Undefined", Opponent* p = NULL)
{
	cout << "Begin "<<playerID<<" turn!" << endl;
	cout << "Known information about Enemy:" << endl;
	GameBoard::drawPlayerData(this, p);
	cout << "Pick a position to shoot:" << endl;
	string playerShellInput;
	getline(cin, playerShellInput);
	Coord shell = Coord(playerShellInput);
	int index = AddPlayerShell(shell, allShips);
		if(coordIsUnique(shell) && shell.getValid())
		{
			if (index >= 0 ) 
			{
				for (int j = 0; j < allShips.size(); j++)
				{
					vector<Coord> Temp = allShips[j].getOccupiedCoords();
					if (find(Temp.begin(), Temp.end(), shell) != Temp.end())
					{
						allShips[j].hit(shell.getX(), shell.getY());
						break;
					}
				}
				cout << "Hit!" << endl;
				addHit(shell);
				
			}
			else
			{
				std::cout << "Miss!" << endl;
				addMiss(shell);
				
			}
			return shell;
		}else
		{
			return Coord(-1, -1);
		}
	
	
}
//Handles turning a User-inputted string into a valid ship configuration, returns a decoded list of ships
// INPUTS: password (string)
// OUTPUTS: decodedShips (vector<ship>)
// Depends on: None
vector<Ship> Player::decodePassword(string password)
{
	vector<Ship> decodedShips;
	string CoordDecoding;
	for (int i = 0; i < password.size(); i += 4)
	{

		CoordDecoding = string(1, password[i + 1]) + password[i + 2];
		Coord decodedCoord = Coord(CoordDecoding);
		if (Ship::isValidType(string(1, password[i]))) {
			Facing f = password[i + 3] == 'X' ? Horizontal : Vertical;
			decodedShips.push_back(Ship(string(1, password[i]), decodedCoord.getX(), decodedCoord.getY(), f));
		}
		else
		{
			return { Ship("Error", -1,-1, Horizontal) };
		}
	}
	return decodedShips;
}

// encodes a list of ships into a string into the right format 
string Player::encodePassword()
{
	string output;
	for (int i = 0; i < _allShips.size(); i++)
	{
		output += _allShips[i].getType();
		Coord shipPos = Coord(_allShips[i].getXpos(), _allShips[i].getYpos());
		output += Coord::getPosUI(shipPos.getX(), shipPos.getY());
		if (_allShips[i].getFacing() == Horizontal)
		{
			output += 'X';
		}
		else
		{
			output += 'Y';
		}

	}
	return output;
}

/*
* handlePassword:
INPUTS: NONE
OUTPUTS: allShips (vector<Ship>)
DEPENDS ON: None
Handles all things to do with password input
*/
vector<Ship> Player::handlePassword()
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
// The logic to handle setup for one human player
vector<Ship> Player::playerUI()
{

	//std::cout << "you will get to view the board once you've placed all your ships, and I do some validating." << endl;
	
	string ShipToSpawn;
	vector<Ship> allShips = {};
	set<string> setOfAllShips = {};
	const vector<string> Ships = { "P (Patrol),", "S (Submarine),","C (Cruiser),","B (Battleship),","A (Carrier)" };
	while (allShips.size() < 5) {
		string pos;
		std::cout << "Begin by positioning your ships, with an X position (0-9), and a Y position (A-J)" << endl;
		std::cout << "Examples Of Valid Coordinates are: d5, E9, 2B, 0a. Examples of Invalid Coordinates: 2k, 12b, b-1, -3B" << endl;
		std::cout << "This is what your board looks like: (by the way, you should enter a coordinate now)" << endl;
		std::cout << "Note: The coordinate you input is the Bottom-left-most position of each ship" << endl;
		placeShips(allShips);
		displayBoard({"Null"});
		std::getline(cin, pos);
		Coord shipPos = Coord(pos);
		if (!shipPos.getValid()) {
			std::cout << "Bad Ships!" << endl;
			continue;
		}
		std::cout << "Pick an orientation: (Valid inputs are: | or -) " << endl;
		string hdg;
		Facing shipDir;
		std::getline(cin, hdg);
		if (hdg == "|") {
			shipDir = Vertical;
		}
		else if (hdg == "-") {
			shipDir = Horizontal;
		}
		else {
			std::cout << "The only valid inputs are: | or -" << endl;
			continue;
		} 
		std::cout << " I won't let you proceed until you've place all five ships. If you try to place two of the same ship, I won't let you. Note: You MUST use CAPITALS." << endl;
		std::cout << "Ship lengths: Patrol: 2 Submarine: Length 3 Cruiser: 3 Battleship: 4 cArrier: 5." << endl;
		std::cout << "Ships yet to be placed: ";
		
		for (int i = 0; i < Ships.size(); i++)
		{
			string F = string(1, Ships[i][0]);
			if (setOfAllShips.find(F) == setOfAllShips.end())
			{
				std::cout << Ships[i];
			}
		}
		std::cout<<std::endl;
		std::getline(cin, ShipToSpawn);
		if (!Ship::isValidType(ShipToSpawn) || setOfAllShips.find(ShipToSpawn) != setOfAllShips.end())
		{
			std::cout << "Invalid Ship type!" << endl;
			continue;
		}

		allShips.push_back(Ship(ShipToSpawn, shipPos.getX(), shipPos.getY(), shipDir));
		if (!Ship::validateShips(allShips))
		{
			allShips.pop_back();
			cout << "Invalid configuration detected! try again!" << endl;
			continue;
		}

		setOfAllShips.insert(ShipToSpawn);
		

		//std::cout << " You have placed all five ships. Allow me to check nothing's wrong with your layout" << endl;
		
	
		
		
		//P2DYS5EXCF8YA5IX
		// TEST LAYOUT: Patrol: D2 |, Submarine: E5 -, Cruiser: F8 | Battleship: D5 | cArrier: I5 -
		// use the above for testing
	}
	// reset the player's view of their own board, so that main can write the state.
	//_ownShipView = { "~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~","~~~~~~~~~~" };
	std::cout << "good news: your setup is valid! I will draw your layout now." << endl;
	return allShips;
}
/*
DisplayBoard()
INPUTS: GamestateInstance (vector<string>)
OUTPUTS: NONE
DEPENDS ON: None
if displayboard gets passed "Null", it draws board data for whichever instance called it
if board data is passed, displayBoard draws that instead.
Note: displayBoard expects a board to be exactly 10 rows. it might crash.
*/
void Player::displayBoard(vector<string> gameStateInstance = {"Null"})
{
	cout << "  ABCDEFGHIJ" << endl;
	const string Xref = "0123456789";
	string out = "";
	for (int i = 0; i < Xref.size(); i++)
	{
		out = "";
		out += Xref[i];
		out += " ";
		if(gameStateInstance != vector<string>{"Null"})
		{
			out += gameStateInstance[i];
		}
		else 
		{
			out += _ownShipView[i];
		}
		cout << GameBoard::colorise(out) << endl;
	}
}
/*
 handleShips
 inputs: allShips (vector<ship>), Opponent (Player*)
 outputs: none
 depends on: none
 Responsible for handling updating the player's own view of their ships each turn.
 */
void Player::handleShips(vector<Ship>& allShips, Player* opponent)
{
	const map<string, char> hitRef = {
		{"P",'p'},
		{"S",'s'},
		{"C",'c'},
		{"B",'b'},
		{"A",'a'}
	};
	
	if (opponent != NULL) 
	{
		for (int i = 0; i < opponent->getPlayerMisses().size(); i++)
		{

			addAtPos(Coord(opponent->getPlayerMisses()[i].getX(), opponent->getPlayerMisses()[i].getY()), 'X'); // marks a miss
		}
		for (int i = 0; i < opponent->getPlayerHits().size(); i++)
		{
			addAtPos(Coord(opponent->getPlayerHits()[i].getX(), opponent->getPlayerHits()[i].getY()), 'h'); // The user should not see this, as it should soon be covered up.
		}
	}
	for (int i = 0; i < allShips.size(); i++)
	{
		vector<Coord> shipOccu = allShips[i].getOccupiedCoords();

		for (int j = 0; j < shipOccu.size(); j++)
		{
			Coord CurrentCoord = shipOccu[j];

			if(_ownShipView[CurrentCoord.getX()][CurrentCoord.getY()] == 'h') // this bit here makes sure the user is unlikely to see this marker
			{
				addAtPos(Coord(CurrentCoord.getX(), CurrentCoord.getY()), hitRef.at(allShips[i].getType()));
			}
			else
			{
				addAtPos(Coord(CurrentCoord.getX(), CurrentCoord.getY()), allShips[i].getType()[0]);
			}


		}
		
	}
	for (int i = 0; i < _ownShipView.size(); i++) // this bit removes any leftovers. 
	{
		for (int j = 0; j < _ownShipView[i].size(); j++)
		{
			if (_ownShipView[i][j] == 'h')
			{
				addAtPos(Coord(i, j), 'X');
			}
		}
	}
}
/*
setUpPlayer()
inputs: allShips (vector<Ship>)
outputs: Player *(this)
Calls the manual setup if the password system was skipped
*/
bool Player::setupPlayer(vector<Ship>& allShips)
{
	
	
	if (allShips.size() <= 0)
	{
		_allShips = playerUI();
	}else
	{
		_allShips = allShips;
	}
	if (_allShips[0].getType() == "Error")
	{
		cout << "It looks like an error happened!" << endl;
		return false;
		
	}
	return true;
}
// does what it says on the tin
/*
initialiseOpponent()
inputs: none
outputs: Opponent (Player)
uses RNG to set up a computer-driven opponent.
*/
Player Player::initialiseOpponent()
{
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
	"P2DXS5EYC8FXB5DXA5IY",
	"A4FXB9JXS2IYP3BYC5CX",
	"A4FYB9JYS2IXP3BXC5CY",
	"P2DYS4FYC9JXB6HXA7FX",
	"C2HXP4EYB8IXA7AYS0HX",
	"A4GXS7JYP2DYC8GXB6FX"
	};
	srand(time(0));
	AIShips = Player::decodePassword(potentialPositions[rand() % potentialPositions.size()]);
	Player PTwo = Player(AIShips);
	_allShips = AIShips;
	return PTwo;
}
Coord Player::TakeTurn(string PlayerID, Opponent* o)
{
	return PlayerShellUI(o->getAllShips(), "Player", o);
}
// the main game loop
/*
turnLoop
inputs: POne (Player*) o(Opponent*)
outputs: none
depends on: none
This loop is responsible for making the turn system work, and checking for victory every turn. 
*/
int Player::turnLoop(Player* POne, Opponent* o)
{

	bool GBTurn = true;
	int windetect = 0;
	while (true) { 
		windetect = Player::determineWin(POne->getAllShips(), o->getAllShips());
		if (windetect == -1)
		{
			cout << "AI Win!";
			return 0;
		}
		if (windetect == 1)
		{
			cout << "Human Win!";
			return 0;
		}
		if (GBTurn)
		{
			/*
			* This while loop is delibrately weird.
			* Because the condition is a UI function, it doesn't make senseto have to execute it twice
			* if the player tries an invalid coordinate. Instead, what we do is very simple, and clever.
			* Because the conditon is evaluated repeatedly, which would require executing the function,
			* that therefore means we can let a player try again, by evaluating the conditon on each loop.
			*/
			while (POne->TakeTurn("Player", o ) == Coord(-1, -1))
			{
				cout << "Try Again!" << endl;
			};
			GBTurn = false;
		}
		else
		{
			//AI's move.


			//cout << Coord::getPosUI(AIShot.getX(), AIShot.getY(), AIShot) << endl;
			/*
			though it may not seem so, this conditon has a future purpose.
			If Player versus player is to be implemented, this
			o != NULL check means we can change the computer opponent
			for a second player, which is far, far simpler than the alternative.
			I can just call the setup routine for each human player.
			With o != NULL:
			...
			else
			{
			 while(PTwo -> TakeTurn(POne->getAllShips(), "Player 2", POne) != Coord(-1,-1))
			 {
			  cout << "Try again" << endl;

			 }

			}
			Without o != NULL:
			Steps involved:
			 - Alter the Opponent Class's TakeTurn to accept Human input
			 - Process the Player's input in the opponent class, calling the player input processing routine
			 from either inside Opponent or passing raw player input to Player, and processing it there
			In summary:
			 the  o != NULL check saves awkwardness for future me.
			*/
			
			
			o->TakeTurn("AI", POne);
			GBTurn = true;

		}

	}
}
