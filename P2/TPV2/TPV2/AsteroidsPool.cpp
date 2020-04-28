#include "AsteroidsPool.h"


AsteroidsPool::AsteroidsPool():AsteroidsPool(20)
{
}

AsteroidsPool::AsteroidsPool(std::size_t n):pool_(n) {
	for (Entity* e : pool_.getPool()) {
		e->addComponent<Transform>();
		e->addComponent<Rotation>();
		e->addComponent<AsteroidLifeTime>();
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

Entity* AsteroidsPool::construct_(double x, double y, double r,Vector2D velocity, int gen)
{
	Entity* e = pool_.getObj();
	if (e != nullptr) {
		e->setActive(true);
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		tr->position_.set(x, y);
		tr->width_ = 8 + 13 * gen;
		tr->height_ = tr->width_; //son igual de anchos como de alto
		tr->velocity_ = velocity;
		e->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime)->SetGen(gen);
		e->getComponent<Rotation>(ecs::Rotation)->rotation_ = r; //fija la verlocidad de la rotacion
	}
	return e;
}

void AsteroidsPool::destroy_(Entity* p)
{
	pool_.relObj(p);
}
