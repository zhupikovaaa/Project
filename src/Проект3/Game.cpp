#include "Game.h"
#include "Tank.h"
#include "Bullet.h"



Game::Game(): field_(START_NUMBER_OF_LIFES, START_NUMBER_OF_SCORES), 
	myTank_(tank_.createGameObject(field_, MY_START_POSITION_X, MY_START_POSITION_Y)),
	nObjects_(START_NUMBER_OF_OBJECTS),
	start_(clock()), isGameEnd_(false),
	myPreviousMoveX_(MY_START_POSITION_X),
	myPreviousMoveY_(MY_START_POSITION_Y)
{
	field_.field[MY_START_POSITION_X][MY_START_POSITION_Y] = MY_TANK;

	for (int i = 0; i < nObjects_; ++i)
		objects_.emplace_back(tank_.createGameObject(field_));
	objects_.reserve(50);

	startGame();
}



void Game::startGame(){

	auto iterator = objects_.begin();
	int move;


	while (!isGameEnd_)
	{
		if (_kbhit())
		{
			move = _getch();
			if (move == DEFAULT)
				move = _getch();
			moveMyTank(move);
		}

		for (iterator = objects_.begin(); iterator < objects_.begin() + nObjects_; )
		{
			if ((*iterator)->isAlive())
			{
				(*iterator)->move(field_);
				makeShoot(iterator);
				++iterator;
			}
			else 
			{
				if (std::dynamic_pointer_cast<Bullet>(*iterator))
					killEnemy(iterator);

				iterator = objects_.erase(iterator);
				nObjects_--;
			}
		}

		Sleep(PAUSE);
		field_.draw();
		std::cout<<"Time: "<<(clock() - start_) / 1000;
	}
}



void Game::makeShoot(std::vector<std::shared_ptr<iGameObject>>::iterator& tank)
{

	if ( ( (*tank)->getX() == myTank_->getX() || (*tank)->getX() == GOLD_POSITION_X ) &&
		std::dynamic_pointer_cast<Tank>(*tank) && !(rand() % 4))
	{

		auto ptr = tank;

		if ( (*tank)->getY() > myTank_->getY())
			objects_.emplace_back(bullet_.createGameObject( (*tank)->getX(), (*tank)->getY(), RIGHT, false)); 
		else
			objects_.emplace_back(bullet_.createGameObject( (*tank)->getX(), (*tank)->getY(), LEFT, false)); 

		tank = ptr;
		nObjects_++;
	}
	else if ( ( (*tank)->getY() == myTank_->getY() || (*tank)->getY() == GOLD_POSITION_Y) &&
		std::dynamic_pointer_cast<Tank>(*tank)  && !(rand() % 4))
	{
		auto ptr = tank;

		if ( (*tank)->getX() > myTank_->getX())
			objects_.emplace_back(bullet_.createGameObject( (*tank)->getX(), (*tank)->getY(), UP, false)); 
		else
			objects_.emplace_back(bullet_.createGameObject( (*tank)->getX(), (*tank)->getY(), DOWN, false));

		tank = ptr;
		nObjects_++;
	}
}



void Game::killEnemy(std::vector<std::shared_ptr<iGameObject>>::iterator& bullet)
{
	auto iterator2 = objects_.begin();

	for (iterator2 = objects_.begin(); iterator2 != objects_.end(); ++iterator2)
		if ((*bullet)->getX() == (*iterator2)->getX() && (*bullet)->getY() == (*iterator2)->getY() &&
			bullet != iterator2)
		{
			(*iterator2)->setDead();
			break;
		}
}


void Game::moveMyTank(int move)
{
	switch (move) 
	{
	case UP:
		myPreviousMoveX_ = myTank_->getX();
		myPreviousMoveY_ = myTank_->getY();
		myTank_->move(field_, UP);
		break;
	case DOWN:
		myPreviousMoveX_ = myTank_->getX();
		myPreviousMoveY_ = myTank_->getY();
		myTank_->move(field_, DOWN);
		break;
	case RIGHT:
		myPreviousMoveX_ = myTank_->getX();
		myPreviousMoveY_ = myTank_->getY();
		myTank_->move(field_, RIGHT);
		break;
	case LEFT:
		myPreviousMoveX_ = myTank_->getX();
		myPreviousMoveY_ = myTank_->getY();
		myTank_->move(field_, LEFT);
		break;
	case SHOOT:
		nObjects_++;
		if (myPreviousMoveX_ > myTank_->getX())
			objects_.emplace_back(bullet_.createGameObject(myTank_->getX(), myTank_->getY(), UP, true));
		else if (myPreviousMoveX_ < myTank_->getX())
			objects_.emplace_back(bullet_.createGameObject(myTank_->getX(), myTank_->getY(), DOWN, true));
		else if (myPreviousMoveY_ > myTank_->getY())
			objects_.emplace_back(bullet_.createGameObject(myTank_->getX(), myTank_->getY(), RIGHT, true));
		else if (myPreviousMoveY_ < myTank_->getY())
			objects_.emplace_back(bullet_.createGameObject(myTank_->getX(), myTank_->getY(), LEFT, true));
		else
			objects_.emplace_back(bullet_.createGameObject(myTank_->getX(), myTank_->getY(), UP, true));
		break;
	}
}