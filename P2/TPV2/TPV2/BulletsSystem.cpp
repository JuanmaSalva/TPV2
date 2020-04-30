#include "BulletsSystem.h"

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	Entity* e = mngr_->addEntity<BulletPool>(pos, vel, width, height);
	if (e != nullptr) e->addToGroup(ecs::_grp_Bullet);
}

void BulletsSystem::init()
{
	windowWidth_ = game_->getWindowWidth();
	windowHeight_ = game_->getWindowHeight();
}

void BulletsSystem::update()
{

	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
		if (!e->isActive()) return; //si no esta activa pasa a la siguiente

		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		tr->position_ = tr->position_ + tr->velocity_;

	}
}

void BulletsSystem::recieve(const msg::Message& msg)
{
}
