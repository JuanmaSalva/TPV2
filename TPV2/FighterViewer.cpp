#include "FighterViewer.h"

FighterViewer::FighterViewer() :
	Component(ecs::FighterViewer)
{
	texture = nullptr;
	transform = nullptr;
}

FighterViewer::~FighterViewer()
{
}

void FighterViewer::init()
{
	texture = game_->getTextureMngr()->getTexture(9);
	transform = GETCMP1_(Transform);
}

void FighterViewer::draw()
{
	texture->render( SDL_Rect{ (int)transform->getPos().getX(), (int)transform->getPos().getY(), (int)transform->getW(), (int)transform->getH() },
					transform->getRot(), SDL_Rect{47, 90, 207, 250});
}
