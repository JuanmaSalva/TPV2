#pragma once
#include "ObjectPool.h"
#include "Asteroid.h"
#include "Component.h"
#include "Bullet.h"

class AsteroidPool:public Component
{
public:
	AsteroidPool();
	virtual ~AsteroidPool(){}

	void generateAsteroids(int n);
	void disableAll();
	void onCollision(Asteroid* a);
	int getNumOfAsteroid() { return numAsteroids; }
	//vector<Asteroid>* getPool() { return asteroidsPool_.getPool(); }
	ObjectPool<Asteroid, 30>* getPool() { return &asteroidsPool_; }

private:
	ObjectPool<Asteroid, 30> asteroidsPool_;
	int numAsteroids; //mantiene una cuenta de los asteroides activos
};

