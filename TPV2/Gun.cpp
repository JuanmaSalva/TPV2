#include "Gun.h"
#include "Entity.h"
#include "Vector2D.h"
#include <math.h>  

Gun::Gun():Gun(SDLK_SPACE)
{	
}

Gun::Gun(SDL_Keycode shoot): Component(ecs::Gun)
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
}

void Gun::update()
{
	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(shoot_)) {
			Vector2D posFin = tr_->getPos();
			posFin = Vector2D(posFin.getX() + (tr_->getH() / 2), posFin.getY());

			double rot = tr_->getRot();
			Vector2D velFin = Vector2D(1*sin(rot),1*cos(rot));

			bulletsPool_->shoot(posFin, velFin,100,100);
		}
	}
}
