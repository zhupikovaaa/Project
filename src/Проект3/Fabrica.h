#ifndef FABRICA_H
#define FABRICA_H

#include "iGameObject.h"

class Fabrica{
public:
	iGameObject* createGameObject(Field& field);
	iGameObject* createGameObject(Field& field, int x, int y);
	iGameObject* createGameObject(int x, int y, DIRECTION d, bool isMy);
};
#endif FABRICA_H