#include "AsteroidPool.h"

AsteroidPool::AsteroidPool() : Component(ecs::AsteroidPool), asteroidsPool_([](Asteroid* o) { return o->inUse_; })
{

}

void AsteroidPool::generateAsteroids(int n)
{
	int width = game_->getWindowWidth();
	int height = game_->getWindowHeight();
	int pos;

	for (int i = 0; i < n; i++) {
		Asteroid* aster = asteroidsPool_.getObj();

		int pared = rand() % 4; //numero aleatorio de 0-3
		Vector2D p;

		switch (pared)
		{
		case 0: //borde izquierdo
			pos = rand() % height;
			p = Vector2D(0, pos);
			break;
		case 1: //borde derecho
			pos = rand() % height;
			p = Vector2D(width, pos);
			break;
		case 2: //borde arriba
			pos = rand() % width;
			p = Vector2D(pos, 0);
			break;
		case 3: //borde abajo
			pos = rand() % width;
			p = Vector2D(pos, height);
			break;
		} //set posticiones

		aster->setPos(p);

		Vector2D c = Vector2D(width / 2, height / 2) + Vector2D((rand() % 100) - 50, (rand() % 100) - 50);

		aster->setVelocity((c - p).normalize() * ((rand() % 9 + 1) / 10.0));
		aster->setGeneracion(rand() % 2 + 1);
		aster->setSize(8 + 13 * aster->getGeneracion(),8 + 13 * aster->getGeneracion());
		aster->inUse_ = true;
	}

	numAsteroids = n;
}

void AsteroidPool::disableAll()
{
	vector<Asteroid*> pool = asteroidsPool_.getPool();

	for (int i = 0; i < pool.size(); i++) {
		pool[i]->inUse_ = false;
	}

	numAsteroids = 0;
}

void AsteroidPool::onCollision(Asteroid* a)
{
	a->inUse_ = false;
	int proxgen = a->getGeneracion() - 1;
	vector<Asteroid*> pool = asteroidsPool_.getPool();
	
	if (a->getGeneracion() > 0) { //si aun se puede dividir
		for (int i = 0; i < 2; i++) {
			Asteroid* nuevo = asteroidsPool_.getObj();

			Vector2D v = a->getVel().rotate(i * 45);
			Vector2D p = a->getPos() + v.normalize();

			nuevo->setVelocity(v);
			nuevo->setPos(p);
			nuevo->setGeneracion(proxgen);
			nuevo->setSize(8 + 13 * a->getGeneracion(), 8 + 13 * a->getGeneracion());
			nuevo->inUse_ = true;
		}
		numAsteroids++;
	}
	else numAsteroids--;
}
