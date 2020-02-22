#include "BulletsViewer.h"

BulletsViewer::BulletsViewer(BulletsPool* b) : Component(ecs::BulletsViewer)
{
	bulletsPool_ = b;
}

BulletsViewer::~BulletsViewer()
{
}

void BulletsViewer::draw()
{
	objPool_ = &bulletsPool_->getPool(); //coge referencia al puntero de pool en si
	vector<Bullet*> pool = objPool_->getPool(); //este es el vector de objetos como tal

	bool terminado = false;
	int i = 0;

	while (!terminado && i < pool.size()) {
		if (pool[i]->inUse_) {
			//aqui se dibujan
		}
		else terminado = true;
		i++;
	}
}
