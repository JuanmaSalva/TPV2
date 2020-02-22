#include "BulletsMotion.h"

BulletsMotion::BulletsMotion(BulletsPool* b): Component(ecs::BulletsMotion)
{
	bulletsPool_ = b;
}

BulletsMotion::~BulletsMotion()
{
}

void BulletsMotion::update()
{
	//esto no se si es realmente el pool del otro componente o es una copia, hay q probar
	objPool_ = &bulletsPool_->getPool(); //coge referencia al puntero de pool en si
	vector<Bullet*> pool = objPool_->getPool(); //este es el vector de objetos como tal

	bool terminado = false;
	int i = 0;

	while (!terminado && i < pool.size()) {
		if (pool[i]->inUse_) {
			Vector2D pos = pool[i]->getPos();
			Vector2D vel = pool[i]->getVel();

			Vector2D posFin = pos + vel;

			if (posFin.getX() < 0.0 || posFin.getY() < 0.0 || posFin.getX() > _WINDOW_WIDTH_ || posFin.getY() > _WINDOW_HEIGHT_) { //se sale de la pantalla
				pool[i]->inUse_ = false; //desactiva la bala en teoria
			}
			else pool[i]->setPos(posFin);

		}
		else terminado = true;
		i++;
	}
}
