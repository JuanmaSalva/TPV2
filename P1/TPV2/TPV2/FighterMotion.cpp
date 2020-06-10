#include "FighterMotion.h"
#include "Entity.h"

FighterMotion::FighterMotion(double drag) :
	Component(ecs::FighterMotion),
	tr_(nullptr),
	drag_(drag)
{
}

FighterMotion::~FighterMotion()
{
}

void FighterMotion::init()
{
	tr_ = GETCMP1_(Transform);
}

void FighterMotion::update()
{
	tr_->setPos(tr_->getPos() + tr_->getVel());

	if (tr_->getPos().getY() < 0 || tr_->getPos().getY() + tr_->getH() > game_->getWindowHeight() ||
		tr_->getPos().getX() < 0 || tr_->getPos().getX() + tr_->getW() > game_->getWindowWidth()) {

		tr_->setPos(tr_->getPos() - tr_->getVel());
		tr_->setVel(tr_->getVel() * -1);
	}


	tr_->setVel(tr_->getVel() * drag_); 
}
