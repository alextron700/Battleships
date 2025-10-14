#pragma once
#include "Player.h"
#include "Coord.h"
#include <vector>
struct Direction {
    int x;
    int y;
};
using namespace std;
class Opponent :
    public Player
{
public:
    Opponent(vector<Ship>& AIShips);
      void setUpOpponent();
      Coord smartSearch();
      Coord TakeTurn(string PlayerID, Player* p);
    Coord Hook(vector<Ship> AllShips, Player pInstance, Coord Pos);
private:
  //  int _difficulty;
    bool _doSmartSearch;
    bool _doHook;
    bool _cheatsAllowed;
    bool _hasHook;
    vector<string> _smartSearchPattern;
    vector<Direction>  _smartSearchOffsets;
    Coord _lastSSCoord;
    int _SSIndex;
    Ship _HookedShip;
    int _HookIndex;
    int _smartCheatIndex;
};

