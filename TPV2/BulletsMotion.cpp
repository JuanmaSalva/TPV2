#include "BulletsMotion.h"


BulletsMotion::BulletsMotion():Component(ecs::BulletsMotion)
{
}

BulletsMotion::~BulletsMotion()
{
}

void BulletsMotion::init()
{
	pool = GETCMP1_(BulletsPool)->getPool()->getPool(); //este es el vector de objetos como tal
}

void BulletsMotion::update()
{
	int i = 0;
	while (i < pool.size()) {
		if (pool[i]->inUse_) {
			Vector2D pos = pool[i]->getPos();
			Vector2D vel = pool[i]->getVel();

			Vector2D posFin = pos + vel;

			if (posFin.getX() < 0.0 || posFin.getY() < 0.0 || posFin.getX() > game_->getWindowWidth() || posFin.getY() > game_->getWindowHeight()) { //se sale de la pantalla
				pool[i]->inUse_ = false; //desactiva la bala en teoria
			}
			else pool[i]->setPos(posFin);

		}
		i++;
	}
}
