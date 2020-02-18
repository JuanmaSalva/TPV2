#include "FighterViewer.h"

FighterViewer::FighterViewer() :
	Component(ecs::Fighter)
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
	texture->render( SDL_Rect{ 10, 10, 100, 100 }, 45.0, SDL_Rect{47, 90, 207, 250});
}
