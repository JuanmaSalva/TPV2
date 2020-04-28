#include "AsteroidsSystem.h"

void AsteroidsSystem::addAsteroids(int n)
{
	for (auto i(0u); i < n; i++) {
		int x = game_->getRandGen()->nextInt(0, game_->getWindowWidth());
		int y = game_->getRandGen()->nextInt(0, game_->getWindowHeight());
		int w = game_->getRandGen()->nextInt(25, 50);
		int h = w;
		int r = game_->getRandGen()->nextInt(1, 2);

		Entity* e = mngr_->addEntity<AsteroidsPool>(x, y, w, h, r);
		if (e != nullptr)
			e->addToGroup(ecs::_grp_Asteroid);
	}
}

void AsteroidsSystem::onCollisionWithBullet(Entity* asteroid, Entity* bullet)
{
}

void AsteroidsSystem::update()
{

	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
		if (!e->isActive()) return; //si no esta activa pasa a la siguiente

		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		auto* rot = e->getComponent<Rotation>(ecs::Rotation);
		tr->position_ = tr->position_ + tr->velocity_;
		tr->rotation_ += rot->rotation_;

	}
}

void AsteroidsSystem::recieve(const msg::Message& msg)
{
}
