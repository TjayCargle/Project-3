#pragma once

#include "Player.h"
class Sorcerer : public Player
{
public:
	Sorcerer(unsigned int _anX, unsigned int _anY, char _aSymb)
	{
		mClass = "Sorcerer";
		mX = _anX;
		mY = _anY;
		mSymbol = _aSymb;
		range = 2;
		maxAtk = 10;
		minAtk = 1;
	};
	~Sorcerer() {};

private:

};
