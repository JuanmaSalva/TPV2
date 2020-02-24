#include "Gun.h"
#include "Entity.h"
#include "Vector2D.h"
#include <math.h>  

Gun::Gun() :Gun(SDLK_SPACE)
{
}

Gun::Gun(SDL_Keycode shoot) : Component(ecs::Gun)
{
	shoot_ = shoot;
}

Gun::~Gun()
{
}

void Gun::init()
{
	bulletsPool_ = GETCMP1_(BulletsPool);
	tr_ = GETCMP1_(Transform);
	time_ = 0;
}


void Gun::update()
{
	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(shoot_) && game_->getTime() - time_ > 250) {
			Vector2D posFin = tr_->getPos();
			double rotacion = -(tr_->getRot()) + 90;

			posFin = Vector2D(posFin.getX() - 5 + (tr_->getW() / 2), posFin.getY() - 5 + (tr_->getH() / 2)); //de aqui sale la posicion del medio del caza
			posFin = Vector2D(posFin.getX() + cos((M_PI * rotacion) / 180) * (tr_->getW() / 2), posFin.getY() - sin((M_PI * rotacion) / 180) * (tr_->getH() / 2)); //calcula el offset

			Vector2D velFin = Vector2D(1 * cos((M_PI * rotacion) / 180), -1 * sin((M_PI * rotacion) / 180));

			bulletsPool_->shoot(posFin, velFin, 100, 100);
			time_ = game_->getTime(); //guarda el tiempo para no poder disparar mas de una bala cada 0.25s
		}
	}
}
