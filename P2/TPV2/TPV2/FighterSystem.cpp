#include "FighterSystem.h"

void FighterSystem::init()
{
	window_width = game_->getWindowWidth();
	window_height = game_->getWindowHeight();

	fighter_ = mngr_->addEntity();
	tr_ = fighter_->addComponent<Transform>(Vector2D(window_width/2 - fighterWidth_/2, window_height/2 - fighterHeight_/2),
		Vector2D(),fighterWidth_, fighterHeight_, 0); 
	fighter_->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::Airplanes));
	mngr_->setHandler(ecs::_hdlr_Fighter, fighter_);
	fighter_->addComponent<Health>(3);
}



void FighterSystem::update()
{
	if (!mngr_->getGameState()->getParado()) {
		auto ih = InputHandler::instance();
		assert(tr_ != nullptr);

		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_RIGHT)) {
				tr_->rotation_ = tr_->rotation_ + 10;
			}
			else if (ih->isKeyDown(SDLK_LEFT)) {
				tr_->rotation_ = tr_->rotation_ - 10;
			}
			else if (ih->isKeyDown(SDLK_UP)) {
				auto nv = Vector2D(0, -1).rotate(tr_->rotation_);
				tr_->velocity_ = nv * (tr_->velocity_.magnitude() + 0.5);
			}
		}

		tr_->position_ = tr_->position_ + tr_->velocity_;
		int x = tr_->position_.getX();
		int y = tr_->position_.getY();

		tr_->velocity_ = tr_->velocity_ * drag_;

		if (x <= 0 || x + tr_->width_ >= game_->getWindowWidth() || y <= 0
			|| y + tr_->height_ >= game_->getWindowHeight()) {
			tr_->rotation_ = fmod(tr_->rotation_ + 180.0, 360.0);
			tr_->velocity_ = tr_->velocity_.rotate(180);
		}
	}


}

void FighterSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_FIGHTERASTEROID_COLLISION_: {
		Entity* fighter = static_cast<const msg::AsteroidFighterCollisionMsg&>(msg).fighter;
		if (!fighter->getComponent<Health>(ecs::Health)->removeLife()) { //muerte total
			mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDeath();
		}
		Transform* tr = fighter->getComponent<Transform>(ecs::Transform);
		tr->position_ = Vector2D(window_width / 2 - fighterWidth_ / 2, window_height / 2 - fighterHeight_ / 2);
		tr->rotation_ = 0;
		tr->velocity_ = Vector2D(0, 0);
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullet)) e->setActive(false);
		break;
	}
	default:
		break;
	}
}
