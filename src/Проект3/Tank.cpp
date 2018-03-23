#include <iostream>

#include "Tank.h"

Tank::Tank (Field& field): isMy_(false), life_(true) 
{
		bool isCorrect = false;

		
		while (!isCorrect) 
		{
			x_ = rand()%11 + 2;
			y_ = rand()%46 + 2;

			if (field.field[x_][y_] != BORDER && field.field[x_][y_] != NON_SOLID_WALL &&
				field.field[x_][y_] != MY_TANK && field.field[x_][y_] != ENEMY &&
				field.field[x_][y_] != AURUM && field.field[x_][y_] != SOLID_WALL &&
				field.field[x_ + 1][y_] != ENEMY && field.field[x_ - 1][y_] != ENEMY &&
				field.field[x_][y_ - 1] != ENEMY && field.field[x_][y_ + 1] != ENEMY &&
				x_ != MY_START_POSITION_X && y_ != MY_START_POSITION_Y &&
				x_ != GOLD_POSITION_X && y_ != GOLD_POSITION_Y)
			{
					field.field[x_][y_] = ENEMY;
					isCorrect = true;
			}
		}
	};



Tank::Tank (Field& field, int x, int y): x_(x), y_(y), isMy_(true), life_(true)
{
		field.field[x_][y_] = MY_TANK;
}



void Tank::move (Field& field, DIRECTION d = DEFAULT)
{
		if(d == DEFAULT)
		{
			int randMove = rand() % 4;
			if (randMove == 0)
				d = UP;
			else if (randMove == 1)
				d = DOWN;
			else if (randMove == 2)
				d = RIGHT;
			else
				d = LEFT;
		}

		switch (d)
		{
		case UP :
			if (field.field[x_-1][y_] != BORDER && field.field[x_-1][y_] != MY_TANK &&
				 field.field[x_-1][y_] != NON_SOLID_WALL && field.field[x_-1][y_] != ENEMY &&
				 field.field[x_-1][y_] != SOLID_WALL && field.field[x_-1][y_] != AURUM) 
			{
				 field.field[x_][y_] = EMPTY;
				  x_--;
					if (isMy_)
						field.field[x_][y_] = MY_TANK;
					else
				  field.field[x_][y_] = ENEMY;
			}
			break;
		case DOWN :
			if (field.field[x_+1][y_] != BORDER && field.field[x_+1][y_] != MY_TANK &&
				 field.field[x_+1][y_] != NON_SOLID_WALL && field.field[x_+1][y_] != ENEMY &&
				 field.field[x_+1][y_] != SOLID_WALL && field.field[x_+1][y_] != AURUM) 
			{
				 field.field[x_][y_] = EMPTY;
				 x_++;
				 if (isMy_)
					 field.field[x_][y_] = MY_TANK;
				 else
				   field.field[x_][y_] = ENEMY;
			}
			break;
		case RIGHT :
			if (field.field[x_][y_-1] != BORDER && field.field[x_][y_-1] != MY_TANK &&
				 field.field[x_][y_-1] != NON_SOLID_WALL && field.field[x_][y_-1] != ENEMY &&
				 field.field[x_][y_-1] != SOLID_WALL && field.field[x_][y_-1] != AURUM) 
			{
				 field.field[x_][y_] = EMPTY;
				 y_--;
				 if (isMy_)
					 field.field[x_][y_] = MY_TANK;
				 else
				   field.field[x_][y_] = ENEMY;
			}
			break;
		case LEFT :
			if (field.field[x_][y_+1] != BORDER && field.field[x_][y_+1] != MY_TANK &&
				 field.field[x_][y_+1] != NON_SOLID_WALL && field.field[x_][y_+1] != ENEMY &&
				 field.field[x_][y_+1] != SOLID_WALL && field.field[x_][y_+1] != AURUM)
			{
				 field.field[x_][y_] = EMPTY;
				 y_++;
				 if (isMy_)
					 field.field[x_][y_] = MY_TANK;
				 else
				   field.field[x_][y_] = ENEMY;
			}
			break;
			
		}
}



inline bool Tank::isAlive() const
{
	return life_;
}



void Tank::setDead(){
	life_ = false;
}



inline int Tank::getX() const
{
	return x_;
}



inline int Tank::getY() const
{
	return y_;
}