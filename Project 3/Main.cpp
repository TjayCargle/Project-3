#pragma once
#include "Game.h"

#include <conio.h>
#define VK_BackSpace      8
#define VK_RETURN         13
#define VK_ESCAPE         27
#define VK_UP             72
#define VK_DOWN           80
#define VK_Left           75
#define VK_Right          77

class DTSTimer
{
	unsigned int startTime;
public:
	DTSTimer()
	{
		reset();
	}

	void reset()
	{
		startTime = clock();
	}

	unsigned int getElapsedTime()
	{
		return (clock() - startTime);
	}

	static void delay(const unsigned int milli)
	{
		unsigned int st = clock();
		while (clock() - st < milli) {}
	}

};


int main(int argc, char ** argv)
{

	//Also need this for memory leak code stuff
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);


	DTSTimer myTimer;
	Game theGame;
	theGame.Start();
	while (theGame.isGameOver() == false)
	{
		if (_kbhit())
		{
			char yo = _getch();

			if (yo == -32)
				yo = _getch();


		
			if (yo == VK_ESCAPE)
				break;


			if (yo == VK_UP)
			{
				
				theGame.upPressed();
			}
			if (yo == VK_DOWN)
			{

				theGame.downPressed();
			}
			if (yo == VK_Right)
			{

				theGame.rightPressed();
			}
			if (yo == VK_Left)
			{

				theGame.leftPressed();
			}
			if (yo == VK_RETURN)
			{
				theGame.returnedPressed();

			}


		}
	
		system("cls");
		theGame.Display();
		//theGame.Update();



		myTimer.delay(250);


	}

	return 0;
}