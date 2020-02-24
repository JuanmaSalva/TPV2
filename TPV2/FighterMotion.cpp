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
	tr_->setVel(tr_->getVel() * drag_);
}
