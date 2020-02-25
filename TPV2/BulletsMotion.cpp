#include "BulletsMotion.h"


BulletsMotion::BulletsMotion():Component(ecs::BulletsMotion)
{
}

BulletsMotion::~BulletsMotion()
{
}

void BulletsMotion::init()
{
	bulletsPool_ = GETCMP1_(BulletsPool);
}

void BulletsMotion::update()
{

	//esto no se si es realmente el pool del otro componente o es una copia, hay q probar
	objPool_ = bulletsPool_->getPool(); //coge referencia al puntero de pool en si
	vector<Bullet*> pool = objPool_->getPool(); //este es el vector de objetos como tal

	int i = 0;

	while (i < pool.size()) {
		if (pool[i]->inUse_) {
			Vector2D pos = pool[i]->getPos();
			Vector2D vel = pool[i]->getVel();

			Vector2D posFin = pos + vel;

			if (posFin.getX() < 0.0 || posFin.getY() < 0.0 || posFin.getX() > _WINDOW_WIDTH_ || posFin.getY() > _WINDOW_HEIGHT_) { //se sale de la pantalla
				pool[i]->inUse_ = false; //desactiva la bala en teoria
			}
			else pool[i]->setPos(posFin);

		}
		i++;
	}
}
