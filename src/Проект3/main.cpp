#include <iostream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <memory>
#include <Windows.h>
#include <ctime>

#include "Fabrica.h"
#include "iGameObject.h"
#include "Tank.h"
#include "Bullet.h"

int main()
{
	srand(time(0));
	std::vector<std::shared_ptr<iGameObject>> objects;

	Field field(3, 0);
	Fabrica bullet;
	Fabrica tank;

	std::shared_ptr<iGameObject> myTank(tank.createGameObject(field, MY_START_POSITION_X, MY_START_POSITION_Y));

	int nObjects = 5;
	int start = clock();

	for (int i = 0; i < nObjects; ++i)
		objects.emplace_back(tank.createGameObject(field));
	objects.reserve(50);

	auto iterator = objects.begin();
	auto iterator2 = objects.begin();
	int move;
	int myPreviousMoveX = MY_START_POSITION_X;
	int myPreviousMoveY = MY_START_POSITION_Y;

	while (true)
	{
		if (_kbhit())
		{
			move = _getch();
				if (move == DEFAULT)
					move = _getch();
				switch (move) 
				{
				case UP:
					myPreviousMoveX = myTank->getX();
					myPreviousMoveY = myTank->getY();
					myTank->move(field, UP);
					break;
				case DOWN:
					myPreviousMoveX = myTank->getX();
					myPreviousMoveY = myTank->getY();
					myTank->move(field, DOWN);
					break;
				case RIGHT:
					myPreviousMoveX = myTank->getX();
					myPreviousMoveY = myTank->getY();
					myTank->move(field, RIGHT);
					break;
				case LEFT:
					myPreviousMoveX = myTank->getX();
					myPreviousMoveY = myTank->getY();
					myTank->move(field, LEFT);
					break;
				case SHOOT:
					nObjects++;
					if (myPreviousMoveX > myTank->getX())
						objects.emplace_back(bullet.createGameObject(myTank->getX(), myTank->getY(), UP, true));
					else if (myPreviousMoveX < myTank->getX())
						objects.emplace_back(bullet.createGameObject(myTank->getX(), myTank->getY(), DOWN, true));
					else if (myPreviousMoveY > myTank->getY())
						objects.emplace_back(bullet.createGameObject(myTank->getX(), myTank->getY(), RIGHT, true));
					else if (myPreviousMoveY < myTank->getY())
						objects.emplace_back(bullet.createGameObject(myTank->getX(), myTank->getY(), LEFT, true));
					else
						objects.emplace_back(bullet.createGameObject(myTank->getX(), myTank->getY(), UP, true));
					break;
				}
		}

		for (iterator = objects.begin(); iterator < objects.begin() + nObjects; )
		{
			if ((*iterator)->isAlive())
			{
				(*iterator)->move(field);
				if ( ( (*iterator)->getX() == myTank->getX() || (*iterator)->getX() == GOLD_POSITION_X ) &&
					std::dynamic_pointer_cast<Tank>(*iterator) && !(rand() % 3))
				{
					auto ptr = iterator;

					if ((*iterator)->getY() > myTank->getY())
						objects.emplace_back(bullet.createGameObject((*iterator)->getX(), (*iterator)->getY(), RIGHT, false)); 
					else
						objects.emplace_back(bullet.createGameObject((*iterator)->getX(), (*iterator)->getY(), LEFT, false)); 

					nObjects++;
					iterator = ptr;
				}
				else if ( ( (*iterator)->getY() == myTank->getY() || (*iterator)->getY() == GOLD_POSITION_Y) &&
					std::dynamic_pointer_cast<Tank>(*iterator)  && !(rand() % 3))
				{
					auto ptr = iterator;

					if ((*iterator)->getX() > myTank->getX())
						objects.emplace_back(bullet.createGameObject((*iterator)->getX(), (*iterator)->getY(), UP, false)); 
					else
						objects.emplace_back(bullet.createGameObject((*iterator)->getX(), (*iterator)->getY(), DOWN, false));

					nObjects++;
					iterator = ptr;
				}
				++iterator;
			}
			else 
			{
				if (std::dynamic_pointer_cast<Bullet>(*iterator))
					for (iterator2 = objects.begin(); iterator2 != objects.end(); ++iterator2)
						if ((*iterator)->getX() == (*iterator2)->getX() && (*iterator)->getY() == (*iterator2)->getY() &&
							iterator != iterator2)
						{
							 (*iterator2)->setDead();
							 break;
						}

				iterator = objects.erase(iterator);
				nObjects--;
			}
		}
		Sleep(500);
		field.draw();
		std::cout<<"Time: "<<(clock() - start) / 1000;
	}

	system("pause");
	return 0;
}