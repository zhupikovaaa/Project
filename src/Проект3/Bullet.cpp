#include "Bullet.h"

Bullet::Bullet(int x, int y, DIRECTION d, bool isMy = false): x_(x), y_(y), direction_(d), isMy_(isMy), life_(true)
{}



void Bullet::move (Field& field, DIRECTION d = DEFAULT){

	if (field.field[x_][y_] != MY_TANK && field.field[x_][y_] != ENEMY)
		field.field[x_][y_] = EMPTY;

	switch (direction_)
	{
	case UP:
		x_--;
		break;
	case DOWN:
		x_++;
		break;
	case RIGHT:
		y_--;
		break;
	case LEFT:
		y_++;
		break;
	}

	if(field.field[x_][y_] == MY_TANK)
	{
		if (!isMy_)
		{
			field.decreaseLifes();
		}
		life_ = false;
		return;
	}
	else if (field.field[x_][y_] == SOLID_WALL)
	{
		field.field[x_][y_] = NON_SOLID_WALL;
		life_ = false;
		return;
	}
	else if (field.field[x_][y_] == NON_SOLID_WALL)
	{
		field.field[x_][y_] = EMPTY;
		life_ = false;
		return;
	}
	else if (field.field[x_][y_] == ENEMY)
	{
		if (isMy_)
		{
			field.field[x_][y_] = EMPTY;
			field.increaseScore();
		}
		life_ = false;
		return;
	}
	else if (field.field[x_][y_] == AURUM)
	{
		field.endGame();
		life_ = false;
		return;
	}
	else if (field.field[x_][y_] == BORDER)
	{
		life_ = false;
		return;
	}
	else if (field.field[x_][y_] == BULLET)
	{
		life_ = false;
		return;
	}

	field.field[x_][y_] = BULLET;
}



inline bool Bullet::isAlive() const
{
	return life_;
}



void Bullet::setDead(){
	life_ = false;
}



inline int Bullet::getX() const
{
	return x_;
}



inline int Bullet::getY() const
{
	return y_;
}

