#include "BulletsViewer.h"

BulletsViewer::BulletsViewer() : Component(ecs::BulletsViewer)
{

	
}

BulletsViewer::~BulletsViewer()
{
}


void BulletsViewer::init()
{
	bulletsPool_ = GETCMP1_(BulletsPool);
	texture = game_->getTextureMngr()->getTexture(11);
	objPool_ = bulletsPool_->getPool(); //coge referencia al puntero de pool en si
	pool = objPool_->getPool(); //este es el vector de objetos como tal
}

void BulletsViewer::draw()
{

	int i = 0;

	while (i < pool.size()) {
		if (pool[i]->inUse_) {
			texture->render(SDL_Rect{(int)pool[i]->getPos().getX(),(int)pool[i]->getPos().getY(),4,4});
		}
		i++;
	}
}

