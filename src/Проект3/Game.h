#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <memory>
#include <Windows.h>
#include <ctime>

#include "iGameObject.h"
#include "Fabrica.h"

const int START_NUMBER_OF_OBJECTS = 5;
const int START_NUMBER_OF_LIFES = 3;
const int START_NUMBER_OF_SCORES = 0;
const int PAUSE = 500;

class Game
{
public:
	Game();
	void startGame();
	void makeShoot(std::vector<std::shared_ptr<iGameObject>>::iterator& tank);
	void killEnemy(std::vector<std::shared_ptr<iGameObject>>::iterator& bullet);
	void moveMyTank(int move);

private:
	std::vector<std::shared_ptr<iGameObject>> objects_;
	std::shared_ptr<iGameObject> myTank_;
	Field field_;
	Fabrica bullet_;
	Fabrica tank_;
	int nObjects_;
	int start_;
	bool isGameEnd_;
	int myPreviousMoveX_;
	int myPreviousMoveY_;
};
#endif GAME_H
