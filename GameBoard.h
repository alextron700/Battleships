#pragma once
#include <string>
#include <vector>
#include "Coord.h"
#include "Ship.h"
#include "Player.h"
#include <set>
#include <map>
using namespace std;
/*Note: GameBoard technically handles both a player's view of their ships AND their view of the opponent
Each instance Player only needs one instance of GameBoard, thanks to this feature
 */
class GameBoard
{
public:
	GameBoard(vector<string> gameState);
	static void drawPlayerData(Player* data, Player* opponent);
	void updateState(Player instanceToUpdate, Coord Position, char newStuff);
	void drawState(bool addPosRefrence);
	static void drawRawData(vector<string> rawData);
	static string colorise(string input);

		
private:
	vector<string> _state;
	
	
};

