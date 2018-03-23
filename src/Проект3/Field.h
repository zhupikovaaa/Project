#ifndef FIELD_H
#define FIELD_H

const int HEIGHT = 14;
const int WIDTH = 50;

const char ENEMY = 'W';
const char MY_TANK = '=';
const char SOLID_WALL = 'E';
const char NON_SOLID_WALL = 'F';
const char BULLET = '.';
const char AURUM = 'A';
const char BORDER = '#';
const char EMPTY = ' ';

const int MY_START_POSITION_X = 12;
const int MY_START_POSITION_Y = 23;

const int GOLD_POSITION_X = 12;
const int GOLD_POSITION_Y = 25;

class Field
{
public:
	char field [HEIGHT][WIDTH];

	Field(int lifes, int score);
	void draw() const;
	void decreaseLifes();
	void increaseScore();
	void endGame() const;

private:
	int lifes_;
	int score_;
};
#endif FIELD_H