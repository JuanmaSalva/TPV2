#include "BulletsSystem.h"
#include "Score.h"

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

		if (tr->position_.getX() - tr->width_ < 0 || tr->position_.getX() + tr->width_ > windowWidth_) {
			e->setActive(false);
		}
		else if (tr->position_.getY() - tr->height_ < 0 || tr->position_.getY() + tr->height_ > windowHeight_) {
			e->setActive(false);
		}
	}
}

void BulletsSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_BULLETASTEROID_COLLISION_: {
		Entity* bullet = static_cast<const msg::BulletAsteroidCollisionMsg&>(msg).bullet;
		bullet->setActive(false);
		mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score)->points_++;
		
		break;
	}
	default:
		break;
	}
}
