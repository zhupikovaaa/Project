#ifndef IGAMEOJECT_H
#define IGAMEOJECT_H

#include "Field.h"


const enum DIRECTION {UP = 72, DOWN = 80, RIGHT = 75, LEFT = 77, SHOOT = 32, DEFAULT = 224};

class iGameObject
{
public:
	virtual void move(Field& field, DIRECTION d = DEFAULT) = 0;
	virtual inline bool isAlive() const = 0;
	virtual void setDead() = 0;
	virtual inline int getX() const = 0;
	virtual inline int getY() const = 0;
};

#endif IGAMEOJECT_H