#pragma once
#include "Player.h"
class Archer: public Player
{
public:
	Archer(unsigned int _anX, unsigned int _anY, char _aSymb) 
	{
		mClass = "Archer"; 
		mX = _anX;
		mY = _anY;
		mSymbol = _aSymb; 
		range = 4;
		maxAtk = 7;
		minAtk = 2;
	};
	~Archer() {};

private:

};
