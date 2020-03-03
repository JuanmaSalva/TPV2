#include "AsteroidsViewer.h"

AsteroidsViewer::AsteroidsViewer() : Component(ecs::AsteroidsViewer)
{
}

void AsteroidsViewer::init()
{
	asterPool_ = GETCMP1_(AsteroidPool);
	texture_ = game_->getTextureMngr()->getTexture(8);
	objPool_ = asterPool_->getPool();
	pool = objPool_->getPool(); //este es el vector de objetos como tal
}

void AsteroidsViewer::draw()
{
	for (int i = 0; i < pool.size(); i++) {
		if (pool[i]->inUse_) {
			texture_->render(SDL_Rect{ (int)pool[i]->getPos().getX(),(int)pool[i]->getPos().getY(),pool[i]->getScaleX(),pool[i]->getScaleY() }, pool[i]->getRotation());
		}
	}
}

