#include "AsteroidsPool.h"


AsteroidsPool::AsteroidsPool():AsteroidsPool(20)
{
}

AsteroidsPool::AsteroidsPool(std::size_t n):pool_(n) {
	for (Entity* e : pool_.getPool()) {
		e->addComponent<Transform>();
		e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Asteroid));
	}
}

AsteroidsPool::~AsteroidsPool()
{
}


void AsteroidsPool::destroy(Entity* p)
{
	AsteroidsPool::instance()->destroy_(p);
}

Entity* AsteroidsPool::construct_(double x, double y, double w, double h)
{
	Entity* e = pool_.getObj();
	if (e != nullptr) {
		e->setActive(true);
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		tr->position_.set(x, y);
		tr->width_ = w;
		tr->height_ = w;
	}
	return e;
}

void AsteroidsPool::destroy_(Entity* p)
{
	pool_.relObj(p);
}
