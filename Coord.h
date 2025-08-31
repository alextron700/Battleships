#pragma once
#include <string>
#include <algorithm>
using namespace std;
class Coord
{
public:
	Coord(int Xpos, int Ypos);
	Coord(std::string pos);
	int getX();
	int getY();
	std::string getPosUI(int posX, int posY);
	bool getValid();
	// this was an addition I did not expect I needed, I relied on artificial sources, due to not
	// knowing how to handle the error this fixed. 
	bool operator<(const Coord& other) const {
		if (this->_posX != other._posX) {
			return this->_posX < other._posX;
		}
		return this->_posY < other._posY;
	}
	bool operator==(const Coord& other) const {
		return _posX == other._posX && _posY == other._posY;
	}
private:
	int _posX;
	int _posY;
	bool _isValid;
};

