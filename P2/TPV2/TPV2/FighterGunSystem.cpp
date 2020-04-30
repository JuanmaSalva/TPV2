#include "FighterGunSystem.h"

void FighterGunSystem::update()
{
	if (!mngr_->getGameState()->getParado()) {
		auto ih = InputHandler::instance();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_SPACE) && game_->getTime() - time_ > 250){
			Transform* tr = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);
			Vector2D posFinal = tr->position_;
			double rotacion = -(tr->rotation_) + 90;

			posFinal = Vector2D(posFinal.getX() - 2 + (tr->width_ / 2), posFinal.getY() - 2 + (tr->height_ / 2)); //de aqui sale la posicion del medio del caza
			posFinal = Vector2D(posFinal.getX() + cos((M_PI * rotacion) / 180) * (tr->width_ / 2), posFinal.getY() - sin((M_PI * rotacion) / 180) * (tr->height_ / 2)); //calcula el offset
		
			Vector2D velFin = Vector2D(5 * cos((M_PI * rotacion) / 180), -5 * sin((M_PI * rotacion) / 180));
			velFin = velFin + tr->velocity_;

			mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->shoot(posFinal, velFin, 5, 5);
			time_ = game_->getTime();
		}
	}
}
