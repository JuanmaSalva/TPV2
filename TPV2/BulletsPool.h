#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Bullet.h"

class Asteroid;
class Bullet;

class BulletsPool:public Component
{
public:
	BulletsPool();
	virtual ~BulletsPool();

	void shoot(Vector2D pos, Vector2D vel, double w, double h);
	void disablAll();
	void  onCollision(Bullet* b, Asteroid* a);
	ObjectPool<Bullet, 10>* getPool();

private:
	ObjectPool<Bullet,10> bulletsPool_;
};

