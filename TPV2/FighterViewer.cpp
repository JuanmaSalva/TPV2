#include "FighterViewer.h"

FighterViewer::FighterViewer() :
	Component(ecs::FighterViewer)
{
	texture = nullptr;
}

FighterViewer::~FighterViewer()
{
}

void FighterViewer::init()
{
	texture = game_->getTextureMngr()->getTexture(9);
}

void FighterViewer::draw()
{
	texture->render( SDL_Rect{ (int)transform->getPos().getX(), (int)transform->getPos().getY(), (int)transform->getW(), (int)transform->getH() },
					transform->getRot(), SDL_Rect{47, 90, 207, 250});
}
