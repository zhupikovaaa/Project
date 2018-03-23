#ifndef BULLET_H
#define BULLET_H

#include "iGameObject.h"

class Bullet: public iGameObject
{
public:
	Bullet(int x, int y, DIRECTION d, bool isMy);
	virtual void move(Field& field, DIRECTION d);
	virtual inline bool isAlive() const;
	virtual void setDead();
	virtual inline int getX() const;
	virtual inline int getY() const;

private:
	int x_;
	int y_;
	DIRECTION direction_;
	bool isMy_;
	bool life_;
};
#endif BULLET_H