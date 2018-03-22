#include <iostream>
#include <Windows.h>

#include "Field.h"

Field::Field(int lifes, int score): lifes_(lifes), score_(score)
{
	for (int i = 0; i < HEIGHT; ++i)
		for (int j = 0; j < WIDTH; ++j) 
		{
			field[i][j] = EMPTY;
		}

	for (int j = 0; j < WIDTH; ++j) 
	{
		field[1][j] = BORDER;
		field[HEIGHT - 1][j] = BORDER;
	}

	for (int i = 1; i < HEIGHT; ++i) {
		field[i][0] = BORDER;
		field[i][WIDTH - 1] = BORDER;
	}

	field[12][24] = SOLID_WALL;
	field[11][24] = SOLID_WALL;
	field[11][25] = SOLID_WALL;
	field[12][25] = AURUM;
	field[12][26] = SOLID_WALL;
	field[11][26] = SOLID_WALL;


	field[0][44] = static_cast<char>(lifes + 48);
	field[0][45] = 'L'; 
	field[0][46] = 'I'; 
	field[0][47] = 'F'; 
	field[0][48] = 'E';
	field[0][49] = 'S';

	field[0][0] = static_cast<char>(score + 48);
	field[0][1] = 'S'; 
	field[0][2] = 'C'; 
	field[0][3] = 'O'; 
	field[0][4] = 'R';
	field[0][5] = 'E';

	for (int i = 2; i < HEIGHT - 1; ++i)
		for (int j = 1; j < WIDTH - 1; ++j)
		{
			if (i == MY_START_POSITION_X && j == MY_START_POSITION_Y || 
				i == GOLD_POSITION_X && j == GOLD_POSITION_Y)
				continue;
			if (rand()%17 == 0)
				field[i][j] = SOLID_WALL;
	}
}



void Field::draw() const
{
	system("cls");	

	for (int i = 0; i < HEIGHT; ++i) 
	{
		for (int j = 0; j < WIDTH; ++j)
			std::cout<<field[i][j];
		std::cout<<std::endl;
	}
}



void Field::decreaseLifes()
{
	if (lifes_ > 1) 
	{
		lifes_--;
		field[0][44] = static_cast<char>(lifes_ + 48);
	}
	else
		endGame();
}



void Field::increaseScore()
{
	if (score_ < 4) 
	{
		score_++;
		field[0][0] = static_cast<char>(score_ + 48);
	}
	else 
	{
		system("cls");
		std::cout<<"You won!!";
		Sleep(5000);
		exit(1);
	}
}



void Field::endGame() const
{
	system("cls");
	std::cout<<"You lose!!";
	Sleep(5000);
	exit(1);
}