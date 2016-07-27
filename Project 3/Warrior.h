#pragma once

#include "Player.h"
class Warrior : public Player
{
public:
	Warrior(unsigned int _anX, unsigned int _anY, char _aSymb)
	{
		mClass = "Warrior";
		mX = _anX;
		mY = _anY;
		mSymbol = _aSymb;
		range = 1;
		maxAtk = 14;
		minAtk = 7;
	};
	~Warrior() {};

private:

};
