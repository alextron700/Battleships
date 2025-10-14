#include "Coord.h"
#include <iostream>
using namespace std;
Coord::Coord(int Xpos, int Ypos) {
	if (Xpos >= 0 && Xpos <= 9 && Ypos >= 0 && Ypos <= 9) 
	{
		_posX = Xpos;
		_posY = Ypos;
		_isValid = true;
	}
	else 
	{
		_isValid = false;
		_posX = -1; // if the coordinate is invalid, default to an error value
		_posY = -1;
	}
}
// (-1,-1) is used as an error signal, in combination with isValid. So that if a function demands a Coordinate output
// and the current state is invalid, we can technically fulfill the reqirement, while signal
Coord::Coord(string pos) 
{
	_posX = -1;
	_posY = -1;
	if (pos.length() != 2) 
	{
		_isValid = false;
		return;
	}
		const string colRef = "0123456789";
		const string rowRef = "ABCDEFGHIJ";
		const string lowerRowRef = "abcdefghij";
		bool XValid = false;
		bool YValid = false;
		//for (int i = 0; i < 10; i++) {
	    // if(pos[0] != colRef[i] && i >= 9){
		if (colRef.find(pos[0]) == string::npos) 
		{
			std::reverse(pos.begin(), pos.end()); // this is so that coordinates are always number first
		}
		// }
		//}

		for (int i = 0; i < 10; i++) 
		{// convert Xposition to int
			if (colRef[i] == pos[0]) 
			{
				_posX = i;
				XValid = true;
			}
		}

		for (int i = 0; i < 10; i++) 
		{// convert Ypos
			if (rowRef[i] == pos[1] || lowerRowRef[i] == pos[1]) 
			{
				_posY = i;
				YValid = true;
			}
		}
		if (!XValid || !YValid) 
		{
			_isValid = false;
			_posX = -1;
			_posY = -1;
			return;
		}
		_isValid = true;
		return;
}
int Coord::getX() 
{

	if (_isValid) 
	{
		return _posX;
	}
	return -1;
}
int Coord::getY() 
{
	if (_isValid) 
	{
		return _posY;
	}
	return -1;
}
bool Coord::getValid() 
{
	return _isValid;
}
/*
getPosUI()
INPUTS:None
OUTPUTS: Position (String)
Depends on: None
turns a given pair of coordinates to a human readable form.
*/
string Coord::getPosUI(int posX, int posY)
{
	string output;
	const string posRef = "ABCDEFGHIJ";
	if (posY > 9 || posX > 9 || posY < 0 || posX < 0) 
	{
		return "Error"; // Keep position checks in bounds
	}
	output += std::to_string(posX);
	output += posRef[posY];
	cout << output << endl;
		return output;
	
	
}
