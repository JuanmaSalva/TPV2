#include "AsteroidsMotion.h"
#include "ObjectPool.h"

AsteroidsMotion::AsteroidsMotion():Component(ecs::AsteroidsMotion)
{
}

void AsteroidsMotion::init()
{
	pool = GETCMP1_(AsteroidPool)->getPool()->getPool();
}

void AsteroidsMotion::update()
{
	for (int i = 0; i < pool.size(); i++) {
		if (pool[i]->inUse_) { //se está usando

			Vector2D pos = pool[i]->getPos();
			Vector2D vel = pool[i]->getVel();

			Vector2D posFin = pos + vel;

			if (posFin.getX() < 0) posFin = Vector2D(game_->getWindowWidth(), posFin.getY());
			else if (posFin.getX() > game_->getWindowWidth()) posFin = Vector2D(0, posFin.getY());
			else if (posFin.getY() < 0) posFin = Vector2D(posFin.getX(), game_->getWindowHeight());
			else if (posFin.getY() > game_->getWindowHeight()) posFin = Vector2D(posFin.getX(), 0);

			pool[i]->setPos(posFin);
			pool[i]->setRotation(pool[i]->getRotation() + 0.5);
		}
	}
}
