#pragma once
#include <string>
#include  <ctime>
using namespace std;
class Player
{
protected:
	unsigned int mX;
	unsigned int mY;
	string mClass;
	char mSymbol;
	int mHealth = 1;
	int mMaxHeakth = 20;
	unsigned int range;
	unsigned int minAtk;
	unsigned int maxAtk;
	int lastMove = 5;
	bool alive = true;
	bool moved = false;
	bool attacked = false;
public:
	Player() 
	{
		mClass = "Null";
		mSymbol = 'd';
		
	};
	~Player() {};

	//Getters
	 int GetX() { return mX; }
	 int GetY() { return mY; }
	int GetHp() { return mHealth; }
	int GetMaxHp() { return mMaxHeakth; }
	int GetlastMove() { return lastMove; }
	unsigned int GetRange(){ return range; }
	char GetSymbol() { return mSymbol; }
	string GetClass() { return mClass; }
	bool didMove() { return moved; }
	bool didAtk() { return attacked; }
	bool isAlive() { return alive; }
	//Setters
	void SetX(int _anX) { mX; }
	void SetY(int _anY) { mY; }
	void SetLastMove(int _aMove) { lastMove = _aMove; }
	void SetHp(unsigned int _someHP) { mHealth = _someHP ; }
	void SetSymbol(unsigned int _aSymb) { mSymbol; }
	void SetClass(unsigned int _someClss) { mClass; }
	void SetMoved(bool _move) { moved = _move; }
	void SetAtked(bool _atk) { attacked = _atk; }
	void calcDmg(int _dmg) 
	{
		mHealth -= _dmg;
		if (mHealth <= 0)
		{
			mHealth = 0;
			if (mSymbol < 90)
				Die('D');
			else
				Die('d');
		}
	}
	//Gameplay Options
	void Attack(Player * _anEnemy) 
	{ srand(unsigned int(time(NULL)* rand())); 
	_anEnemy->calcDmg( (rand() % (maxAtk - minAtk + 1) + minAtk));
	}
	void Move(unsigned int _dir) 
	{
		// dir 0 = up, dir 1 = right, dir 2 = down, dir 3 = left
		if (_dir == 0)
		{
			mY--;
		}
		if (_dir == 1)
		{
			mX++;
		}
		if (_dir == 2)
		{
			mY++;
		}
		if (_dir == 3)
		{
			mX--;
		}
	}
	void Die(char _teamChar) { mHealth = 0; alive = false; mSymbol = _teamChar; }

	//Other

};
