#include "Fabrica.h"
#include "Bullet.h"
#include "Tank.h"

iGameObject* Fabrica::createGameObject(int x, int y, DIRECTION d, bool isMy)
{
	return new Bullet (x, y, d, isMy);
}



iGameObject* Fabrica::createGameObject(Field& field, int x, int y)
{
	return new Tank (field, x, y);
}



iGameObject* Fabrica::createGameObject(Field& field)
{
	return new Tank (field);
}