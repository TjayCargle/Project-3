#pragma once
#include "Archer.h"
#include "Sorcerer.h"
#include "Warrior.h"
#include "DynArray.h"
#include <iostream>
using namespace std;
class Game
{
private:
	char theBoard[6][6];
	DynArray<Player> thePlayers;
	Player * targets[3] = { nullptr };
	Player * turnOrder[6];
	string Messesge[3];
	bool inMenu = true;
	unsigned int menuCarrot = 0;
	bool GameOver = false;
	bool allowMove = false;
	bool allowAtk = false;
	bool inAtkMenu = false;
	bool selectingTarget = false;
	bool end = false;
	bool targetInRange = false;
	bool canMove = true;
public:
	Game() {};
	~Game()
	{
		inMenu = false;
		clearTargets();
		turnOrder[6] = { nullptr };
		thePlayers.clear();
	};
	bool isGameOver() { return GameOver; }
	void Start()
	{
		/*Archer bigArcher(0, 0, 'A');
		Warrior bigWarrior(1, 0, 'W');
		Sorcerer bigSorcerer(0, 1, 'S');
		Archer littleArcher(5, 5, 'a');
		Warrior littleWarrior(4, 5, 'w');
		Sorcerer littleSorcerer(5, 4, 's');*/
		Archer bigArcher(2, 3, 'A');
		Warrior bigWarrior(3, 1, 'W');
		Sorcerer bigSorcerer(3, 2, 'S');
		Archer littleArcher(3, 3, 'a');
		Warrior littleWarrior(3, 4, 'w');
		Sorcerer littleSorcerer(2, 4, 's');
		thePlayers.append(bigArcher);
		thePlayers.append(bigWarrior);
		thePlayers.append(bigSorcerer);
		thePlayers.append(littleArcher);
		thePlayers.append(littleWarrior);
		thePlayers.append(littleSorcerer);

		//Messesge[0] = "Move";
		//Messesge[1] = "Attack";
		//Messesge[2] = "Wait";

		for (unsigned int y = 0; y < 6; y++)
		{
			for (unsigned int x = 0; x < 6; x++)
			{
						theBoard[x][y] = '*';	
			}

		}
		clearTargets();
		RoundStart();
		for (unsigned int y = 0; y < 6; y++)
		{
			for (unsigned int x = 0; x < 6; x++)
			{

				for (unsigned int p = 0; p < thePlayers.size(); p++)
				{
					if (thePlayers[p].GetX() == x && thePlayers[p].GetY() == y)
						theBoard[x][y] = thePlayers[p].GetSymbol();
					
				}
			}

		}
		UpdateTurnOptions();



	}

	void GenerateTurnOrder()
	{
		int iNum = 0;
		srand(unsigned int(time(NULL)* rand()));
		bool indices[6] = { false };
		for (unsigned int i = 0; i < 6; i++)
		{
			indices[i] = false;
		}

		for (unsigned int i = 0; i < 6; i++)
		{
			while (indices[0] == false || indices[1] == false || indices[2] == false || indices[3] == false || indices[4] == false || indices[5] == false)
			{
				iNum = rand() % 6;
				if (indices[iNum] == false)
				{
					if (thePlayers[iNum].isAlive())
					{
						turnOrder[i] = &thePlayers[iNum];
					}
					indices[iNum] = true;
					break;
				}
			}
		}
		if (turnOrder[0] != nullptr)
		{
			turnOrder[0]->SetMoved(false);
			turnOrder[0]->SetAtked(false);
			UpdateTurnOptions();
		}
	}
	void RoundStart()
	{
		GenerateTurnOrder();
		UpdateTurnOptions();
	}

	void WinGame()
	{
		system("cls");
		
		 for (unsigned int i = 0; i < 6; i++)
		{
			if (thePlayers[i].isAlive() == true)
			{
				if (thePlayers[i].GetSymbol() < 90)
				{
					cout << endl << endl << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "UpperCase Team" << "WINS!" << endl;
					break;
				}
				else
				{
					cout << endl << endl << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "LowerCase Team" << "WINS!" << endl;
					break;
				}
		
			}
		}
		 
		 system("pause");

		
	}
	
	void CheckWinGameCondMet()
	{
		unsigned int lowerDead = 0;
		unsigned int upperDead = 0;
		for (unsigned int i = 0; i < 6; i++)
		{
			if (thePlayers[i].isAlive() == false)
			{
				if (thePlayers[i].GetSymbol() < 90)
					upperDead++;
				else
					lowerDead++;
			}
		}

		if (upperDead == 3 || lowerDead == 3)
		{
			WinGame();
			GameOver = true;
		}
		
	}

	void TurnStart()
	{
		clearTargets();
		
		if (turnOrder[0] != nullptr)
		{
			if (turnOrder[0]->isAlive() == true)
			{
				turnOrder[0]->SetMoved(false);
				turnOrder[0]->SetAtked(false);
				UpdateTurnOptions();
			}
			else
			{
				UpdateTurnOrder();
				TurnStart();
			}
			
		}
		else
		{
			RoundStart();
			UpdateTurnOptions();
		}

	}

	void UpdateTurnOrder()
	{
		clearTargets();
		if (turnOrder[0] != nullptr)
		{
			for (unsigned int i = 0; i + 1 < 6; i++)
			{
				turnOrder[i] = turnOrder[i + 1];
				if (turnOrder[i] != nullptr)
				{
					if (turnOrder[i]->isAlive() == false)
					{
						
						turnOrder[i] = turnOrder[i + 1];
					}
				}

			}
			turnOrder[5] = nullptr;

			if (turnOrder[0] != nullptr)
				TurnStart();
		}
		else
		{
			RoundStart();
		}

		if (turnOrder[0] == nullptr)
			RoundStart();
	
		UpdateTurnOptions();
	}
	void UpdateTurnOptions()
	{
		if (allowAtk == false)
		{
			if (turnOrder[0] == nullptr)
			{
				RoundStart();
			}
			else
			{
				areThereOpenSpots();
				if (turnOrder[0]->didMove() == true)
				{
					Messesge[0] = "You have already moved this turn";
					if (Messesge[2] != "Wait")
						Messesge[2] = "Wait";
				}
				else
				{

					if (canMove == true)
					{
						Messesge[0] = "Move";
					}
					else
					{
						Messesge[0] = "No available movement";
					}

					if (turnOrder[0]->didAtk() == true)
					{
						turnOrder[0]->SetMoved(true);
						Messesge[0] = "Cannot move after attacking";
					}
				}
				if (turnOrder[0]->didAtk() == true)
				{
					Messesge[1] = "You have already attacked this turn";
					if (Messesge[2] != "Wait")
						Messesge[2] = "Wait";
				}
				else if(allowAtk == false)
				{

					CheckTargetsInRange();
					if (targetInRange == true)
					{
						Messesge[1] = "Attack";
						getTargets();
					}
					else
						Messesge[1] = "No target in range of attack";
					
					if (Messesge[2] != "Wait")
						Messesge[2] = "Wait";
				}
				else if (allowAtk == true)
				{
					if (turnOrder[0]->didAtk() == true)
						Messesge[1] = "You have already attacked this turn";
					else
					{
						allowAtk = false;
						CheckTargetsInRange();
						if (targetInRange == true)
						{
							Messesge[0] = "Comfirm Attack?";
							if (turnOrder[0]->didMove() == true)
								Messesge[1] = "Cannot move again after attacking";
							else
							{
								Messesge[1] = "Attack and then move";
							}
							Messesge[2] = "Don't attack";
							inMenu = true;
						}
						else
							Messesge[1] = "No target in range of attack";

					
					}
				if (Messesge[2] != "Wait")
					Messesge[2] = "Wait";

			}
			

		}
		



		}
			else if (inAtkMenu == false)
				{
					if (turnOrder[0]->didAtk() == true)
						Messesge[1] = "You have already attacked this turn";
					else
					{
						allowAtk = false;
						CheckTargetsInRange();
						if (targetInRange == true)
						{
							Messesge[0] = "Comfirm Attack?";
							if (turnOrder[0]->didMove() == true)
								Messesge[1] = "Cannot move again after attacking";
							else
							{
								Messesge[1] = "Comfirm attack and end turn?";
							}
							Messesge[2] = "Don't attack";
							inMenu = true;
						}
						else
							Messesge[1] = "No target in range of attack";
					}

					}
	}



	void upPressed()
	{
		if (inMenu == true)
		{
			if (menuCarrot > 0)
				menuCarrot--;
			else if (menuCarrot == 0)
				menuCarrot = 2;

		}
		else
		{
			if (turnOrder[0] != nullptr)
			{
				if (turnOrder[0]->didMove() == false && selectingTarget == false)
				{
					if (allowMove == true)
					{
						if (isOpenSpot(turnOrder[0]->GetX(), turnOrder[0]->GetY() - 1))
						{
							theBoard[turnOrder[0]->GetX()][turnOrder[0]->GetY()] = '*';
							turnOrder[0]->SetLastMove(0);
							turnOrder[0]->Move(0);
							Messesge[0] = "Comfirm Move?";
							CheckTargetsInRange();
							if (turnOrder[0]->didAtk() == true)
								Messesge[1] = "You have already attacked this turn";
							else
							{
								if (targetInRange == false)
								{
									Messesge[1] = "No target after moving";
								}
								else
								{
									Messesge[1] = "Comfirm Move and Attack?";
									getTargets();
								}
							}
							
							Messesge[2] = "Revert";
							inMenu = true;
						}
					}

				}

			}
			
		}
	}
	void downPressed()
	{
		if (inMenu == true)
		{
			if (menuCarrot < 2)
				menuCarrot++;
			else if (menuCarrot == 2)
				menuCarrot = 0;

		}
		else
		{
			if (turnOrder[0] != nullptr)
			{
				if (turnOrder[0]->didMove() == false && selectingTarget == false)
				{
					if (allowMove == true)
					{
						if (isOpenSpot(turnOrder[0]->GetX(), turnOrder[0]->GetY() + 1))
						{
							theBoard[turnOrder[0]->GetX()][turnOrder[0]->GetY()] = '*';
							turnOrder[0]->SetLastMove(2);
							turnOrder[0]->Move(2);
							Messesge[0] = "Comfirm Move?";
							CheckTargetsInRange();
							if (turnOrder[0]->didAtk() == true)
								Messesge[1] = "You have already attacked this turn";
							else
							{
								if (targetInRange == false)
								{
									Messesge[1] = "No target after moving";
								}
								else
								{
									Messesge[1] = "Comfirm Move and Attack?";
									getTargets();
								}
							}
							Messesge[2] = "Revert";
							inMenu = true;
						}
					}

				}


			}
		}
	}

	void rightPressed()
	{
		if (inMenu == false)
		{
			if (turnOrder[0] != nullptr)
			{
				if (turnOrder[0]->didMove() == false && selectingTarget == false)
				{
					if (allowMove == true)
					{
						if (isOpenSpot(turnOrder[0]->GetX() + 1, turnOrder[0]->GetY() ))
						{
							theBoard[turnOrder[0]->GetX()][turnOrder[0]->GetY()] = '*';
							turnOrder[0]->SetLastMove(1);
							turnOrder[0]->Move(1);
							Messesge[0] = "Comfirm Move?";
							CheckTargetsInRange();
							if (turnOrder[0]->didAtk() == true)
								Messesge[1] = "You have already attacked this turn";
							else
							{
								if (targetInRange == false)
								{
									Messesge[1] = "No target after moving";
								}
								else
								{
									Messesge[1] = "Comfirm Move and Attack?";
									getTargets();
								}
							}
							Messesge[2] = "Revert";
							inMenu = true;
						}
					}

				}


			}

		}

	}
	void leftPressed()
	{

		if (inMenu == false)
		{
			if (turnOrder[0] != nullptr)
			{
				if (turnOrder[0]->didMove() == false && selectingTarget == false)
				{
					if (allowMove == true)
					{
						if (isOpenSpot(turnOrder[0]->GetX() -1, turnOrder[0]->GetY() ))
						{
							theBoard[turnOrder[0]->GetX()][turnOrder[0]->GetY()] = '*';
							turnOrder[0]->SetLastMove(3);
							turnOrder[0]->Move(3);
							Messesge[0] = "Comfirm Move?";
							CheckTargetsInRange();
							if (turnOrder[0]->didAtk() == true)
								Messesge[1] = "You have already attacked this turn";
							else
							{
								if (targetInRange == false)
								{
									Messesge[1] = "No target after moving";
								}
								else
								{
									Messesge[1] = "Comfirm Move and Attack?";
									getTargets();
								}
							}
							Messesge[2] = "Revert";
							inMenu = true;
						}
					}

				}

				if (turnOrder[0]->didAtk() == false && selectingTarget == false)
				{
				

				}

			}
		}
	}

	void CheckTargetsInRange()
	{
		targetInRange = false;
		int distance = 0;


		if (turnOrder[0] != nullptr)
			for (int y = 0; y < 6; y++)
			{
				for (int x = 0; x < 6; x++)
				{
					distance = abs(x - turnOrder[0]->GetX()) + abs(y - turnOrder[0]->GetY());
					if (theBoard[x][y] != '*' && distance <= (int)turnOrder[0]->GetRange() && distance != 0 && theBoard[x][y] != 'd'&& theBoard[x][y] != 'D')
					{

						if (theBoard[x][y] > 90 && turnOrder[0]->GetSymbol() < 97 && theBoard[x][y] != 'd'&& theBoard[x][y] != 'D')
							targetInRange = true;
						else if (turnOrder[0]->GetSymbol() > 90 && theBoard[x][y] < 97 && theBoard[x][y] != 'd'&& theBoard[x][y] != 'D')
							targetInRange = true;
					}


				}

			}


	}

	void returnedPressed()
	{

		
		CheckTargetsInRange();

		if (inMenu == true)
		{
			if (allowAtk == false)
			{

				switch (menuCarrot)
				{
				case 0:
					if (Messesge[0] == "Move")
					{
						allowMove = true;
						inMenu = false;
					}
					else if (Messesge[0] == "Comfirm Move?")
					{
						turnOrder[0]->SetMoved(true);
						allowMove = false;

					}
					else if (Messesge[0] == "Comfirm Attack?")
					{

						getTargets();
						allowAtk = true;
						for (int i = 0; i < 3; i++)
						{

							if (targets[i] != nullptr)
							{
								Messesge[i] = "Attack ";
								Messesge[i] += targets[i]->GetSymbol();
							}
							else
							{
								Messesge[i] = "";
							}

						}
						inAtkMenu = true;
						//turnOrder[0]->SetAtked(true);
					}

					break;
				case 1:
					if (Messesge[1] == "Attack")
					{
						//getTargets();
						allowAtk = true;
						
						/*for (int i = 0; i < 3; i++)
						{

							if (targets[i] != nullptr)
							{
								Messesge[i] = "Attack ";
								Messesge[i] += targets[i]->GetSymbol();
							}
							else
							{
								Messesge[i] = "";
							}


						}
						turnOrder[0]->SetAtked(true);*/

					}
					else if (Messesge[1] == "Comfirm Move and Attack?")
					{
						turnOrder[0]->SetMoved(true);
						getTargets();
						allowAtk = true;
						for (int i = 0; i < 3; i++)
						{

							if (targets[i] != nullptr)
							{
								Messesge[i] = "Attack ";
								Messesge[i] += targets[i]->GetSymbol();
							}
							else
							{
								Messesge[i] = "";
							}

						}
						//turnOrder[0]->SetAtked(true);
						inAtkMenu = true;
					}
					else if (Messesge[1] == "Comfirm attack and end turn?")
					{
						getTargets();
						allowAtk = true;
						for (int i = 0; i < 3; i++)
						{

							if (targets[i] != nullptr)
							{
								Messesge[i] = "Attack ";
								Messesge[i] += targets[i]->GetSymbol();
							}
							else
							{
								Messesge[i] = "";
							}

						}
						
						end = true;
						inAtkMenu = true;
						//inMenu = false;

					}
					else if (Messesge[1] == "Comfirm Atk?")
					{
						getTargets();
						allowAtk = true;
						for (int i = 0; i < 3; i++)
						{

							if (targets[i] != nullptr)
							{
								Messesge[i] = "Attack ";
								Messesge[i] += targets[i]->GetSymbol();
							}
							else
							{
								Messesge[i] = "";
							}

						}
						inAtkMenu = true;
						//turnOrder[0]->SetAtked(true);
					}


					break;
				case 2:
					if (Messesge[2] == "Wait")
					{
						UpdateTurnOrder();
					}
					else if (Messesge[2] == "Revert")
					{
						theBoard[turnOrder[0]->GetX()][turnOrder[0]->GetY()] = '*';
						switch (turnOrder[0]->GetlastMove())
						{
						case 0:
							turnOrder[0]->Move(2);
							break;
						case 1:
							turnOrder[0]->Move(3);
							break;
						case 2:
							turnOrder[0]->Move(0);
							break;
						case 3:
							turnOrder[0]->Move(1);
							break;
						}
						Messesge[2] = "Wait";
						UpdateTurnOptions();
						//inMenu = false;
					}
					else if (Messesge[2] == "Don't attack")
					{
						clearTargets();
						allowAtk = false;
						inMenu = true;
					}

					break;
				}

			}
		else if (inAtkMenu == true)
			{

				{
					for (int i = 0; i < 3; i++)
					{
						if (targets[i] != nullptr)
						{
							if (targets[i]->isAlive() == true)
							{
								string checkMessage = "Attack ";
								checkMessage += targets[i]->GetSymbol();
								if (Messesge[menuCarrot] == checkMessage)
								{
									turnOrder[0]->Attack(targets[i]);
									allowAtk = false;
									inAtkMenu = false;
									clearTargets();
									turnOrder[0]->SetAtked(true);
									if (end == true)
									{
										UpdateTurnOrder();
										end = false;
									}
									CheckWinGameCondMet();
								
								}
							}
						}
					}
				}
			}
		}
		UpdateTurnOptions();
	}




	bool isOpenSpot(unsigned int _anX, unsigned int _anY)
	{
		bool open = false;
		if (_anX <= 5 && _anX >= 0 && _anY <= 5 && _anY >= 0)
		{
			if (theBoard[_anX][_anY] == '*')
				open = true;
		}
		return open;
	}
	void areThereOpenSpots()
	{
		if (turnOrder[0] != nullptr)
			if (isOpenSpot(turnOrder[0]->GetX(), turnOrder[0]->GetY() + 1) || isOpenSpot(turnOrder[0]->GetX(), turnOrder[0]->GetY() - 1) || isOpenSpot(turnOrder[0]->GetX() + 1, turnOrder[0]->GetY()) || isOpenSpot(turnOrder[0]->GetX() - 1, turnOrder[0]->GetY()))
				canMove = true;
			else
				canMove = false;
	}

	void getTargets()
	{
		clearTargets();
		int distance = 0;


		if (turnOrder[0] != nullptr)
			for (int y = 0; y < 6; y++)
			{
				for (int x = 0; x < 6; x++)
				{
					distance = abs(x - turnOrder[0]->GetX()) + abs(y - turnOrder[0]->GetY());
					if (theBoard[x][y] != '*' && distance <= (int)turnOrder[0]->GetRange() && distance != 0)
					{

						if (theBoard[x][y] > 90 && turnOrder[0]->GetSymbol() < 97 && theBoard[x][y] != 'D'  && theBoard[x][y] != 'd')
						{
							for (unsigned int i = 0; i < 6; i++)
							{

								if (thePlayers[i].GetSymbol() == theBoard[x][y])
								{
									for (int j = 0; j < 3; j++)
									{
										if (targets[j] == nullptr)
										{
											targets[j] = &(thePlayers[i]);
											break;
										}
									}
								}
							}
						}
						else if (turnOrder[0]->GetSymbol() > 90 && theBoard[x][y] < 97 && theBoard[x][y] != 'D'  && theBoard[x][y] != 'd')
						{
							for (unsigned int i = 0; i < 6; i++)
							{

								if (thePlayers[i].GetSymbol() == theBoard[x][y])
								{
									for (int j = 0; j < 3; j++)
									{
										if (targets[j] == nullptr)
										{
											targets[j] = &(thePlayers[i]);
											break;
										}
									}
								}
							}
						}
					}


				}

			}


	}

	void clearTargets()
	{
		for (int i = 0; i < 3; i++)
		{
			targets[i] = nullptr;
		}
	}
	void Display()
	{
		if (GameOver == false)
		{
			cout << endl << endl << endl;
			cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "Turn Order" << endl;
			for (unsigned int y = 0; y < 6; y++)
			{
				cout << '\t' << '\t' << '\t' << '\t';
				for (unsigned int x = 0; x < 6; x++)
				{
					for (unsigned int p = 0; p < thePlayers.size(); p++)
					{
						if (thePlayers[p].GetX() == x && thePlayers[p].GetY() == y)
							theBoard[x][y] = thePlayers[p].GetSymbol();
					}

					cout << theBoard[x][y];

				}
				if (turnOrder[y] != nullptr)
				{
					if (turnOrder[y] == turnOrder[0])
						cout << '\t' << '\t' << "    " << turnOrder[y]->GetSymbol() << " <-" << endl;
					else
						cout << '\t' << '\t' << "    " << turnOrder[y]->GetSymbol() << endl;
				}
				else
					cout << '\t' << '\t' << "    " << endl;
			}
			cout << endl << endl;
			for (unsigned int p = 0; p < thePlayers.size(); p++)
			{
				if (p == 0)
					cout << '\t' << '\t' << " UpperTeam: ";
				cout << thePlayers[p].GetSymbol() << ": " << thePlayers[p].GetHp() << '/' << thePlayers[p].GetMaxHp() << " ";
				if (p == 2)
					cout << endl << '\t' << '\t' << " LowerTeam: ";

			}
			if (turnOrder[0] != nullptr)
				if (inMenu == true)
				{
					cout << endl << endl << '\t' << '\t' << " Player " << turnOrder[0]->GetSymbol() << " You may..." << endl << endl;
					for (unsigned int i = 0; i < 3; i++)
					{
						if (menuCarrot == i)
						{
							cout << '\t' << '\t' << "> " << Messesge[i] << endl;;
						}
						else
						{
							cout << '\t' << '\t' << "  " << Messesge[i] << endl;
						}

					}
				}
		}
	}



};
