#include "FighterCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"

FighterCtrl::FighterCtrl() :
	FighterCtrl(SDLK_LEFT, SDLK_RIGHT, SDLK_UP) {
}

FighterCtrl::FighterCtrl(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up) :
	Component(ecs::FighterCtrl),
	left_(left),
	right_(right),
	up_(up),
	tr_(nullptr)
{
}

FighterCtrl::~FighterCtrl()
{
}

void FighterCtrl::init()
{
	tr_ = GETCMP1_(Transform);
}

void FighterCtrl::update()
{
	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(up_)) {
			tr_->setVel(tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * tr_->getThrust());
			if (tr_->getVel().magnitude() > tr_->getSpeedLimit()) {
				tr_->setVel(tr_->getVel().normalize() * tr_->getSpeedLimit());
			}
		}
		else if (ih->isKeyDown(right_)) {
			tr_->setRot(tr_->getRot() + 5);
		}
		else if (ih->isKeyDown(left_)) {
			tr_->setRot(tr_->getRot() - 5);
		}
	}
}
