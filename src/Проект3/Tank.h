#ifndef TANK_H
#define TANK_H

#include "iGameObject.h"

class Tank: public iGameObject
{
public:
	Tank(Field& field);
	Tank(Field& field, int x, int y);
	virtual void move(Field& field, DIRECTION d);
	virtual inline bool isAlive() const;
	virtual void setDead();
	virtual inline int getX() const;
	virtual inline int getY() const;

private: 
	int x_;
	int y_;
	bool isMy_;
	bool life_;
};
#endif TANK_H