#include "AsteroidsSystem.h"

void AsteroidsSystem::addAsteroids(int n)
{
	for (auto i(0u); i < n; i++) {
		int x = game_->getRandGen()->nextInt(0, game_->getWindowWidth());
		int y = game_->getRandGen()->nextInt(0, game_->getWindowHeight());
		int w = game_->getRandGen()->nextInt(25, 50);
		int h = w;

		Entity* e = mngr_->addEntity<AsteroidsPool>(x, y, w, h);
		if (e != nullptr)
			e->addToGroup(ecs::_grp_Asteroid);
	}
}

void AsteroidsSystem::onCollisionWithBullet(Entity* asteroid, Entity* bullet)
{
}

void AsteroidsSystem::update()
{
}

void AsteroidsSystem::recieve(const msg::Message& msg)
{
}
