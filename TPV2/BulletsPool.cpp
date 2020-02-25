#include "BulletsPool.h"

BulletsPool::BulletsPool() : Component(ecs::BulletsPool), bulletsPool_([](Bullet* o) { return o->inUse_; })
{
}

BulletsPool::~BulletsPool()
{
}

void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h)
{
	Bullet* b = bulletsPool_.getObj(); //devuelve la primera bala que no se esté usando

	if (b != nullptr) { //si quedan balas
		b->setPos(pos);
		b->setVelocity(vel);
		b->setSize(w, h);
		b->inUse_ = true;
	}

}

void BulletsPool::disablAll()
{
	vector<Bullet*> pool = bulletsPool_.getPool();

	bool terminado = false;
	int i = 0;

	while (!terminado && i < pool.size()) {
		if (pool[i]->inUse_) pool[i]->inUse_ = false;
		else terminado = true;
		i++;
	}

}


//no se si aqui tenemos que mirar si hay colision o no
void BulletsPool::onCollision(Bullet* b, Asteroid* a)
{
	bool encontrado = false;
	int i = 0;
	vector<Bullet*> pool = bulletsPool_.getPool();

	while (!encontrado)
	{
		if (b == pool[i]) {
			b->inUse_ = false;
			encontrado = true;
		}
	}
}

ObjectPool<Bullet, 10>* BulletsPool::getPool()
{
	return &bulletsPool_; //devuelve un puntero al objectpool
}
