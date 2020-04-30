#include "BulletPool.h"

BulletPool::BulletPool():BulletPool(20) {

}

BulletPool::BulletPool(std::size_t n) :pool_(n) {
	for (Entity* e : pool_.getPool()) {
		e->addComponent<Transform>();
		e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::White));
	}
}

BulletPool::~BulletPool()
{
}

void BulletPool::destroy(Entity* p)
{
	BulletPool::instance()->destroy_(p);
}

Entity* BulletPool::construct_(Vector2D pos, Vector2D vel, double width, double height)
{
	Entity* e = pool_.getObj();
	if (e != nullptr) {
		e->setActive(true);
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		tr->position_ = pos;
		tr->velocity_ = vel;
		tr->width_ = width;
		tr->height_ = height;
	}

	return e;
}

void BulletPool::destroy_(Entity* p)
{
	pool_.relObj(p);
}
