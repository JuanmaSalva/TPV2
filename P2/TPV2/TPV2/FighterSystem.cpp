#include "FighterSystem.h"

void FighterSystem::init()
{
	fighter_ = mngr_->addEntity();
	tr_ = fighter_->addComponent<Transform>(Vector2D(200.0, 100), Vector2D(),50, 50, 0);
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

void FighterSystem::onCollisionWithAsteroid(Entity* asteroid)
{
}
