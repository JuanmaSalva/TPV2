#include "FighterViewer.h"

FighterViewer::FighterViewer() :
	Component(ecs::Fighter)
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
	transform = entity_->getComponent<Transform>(ecs::Transform);
}

void FighterViewer::draw()
{
	texture->render( SDL_Rect{ (int)transform->getPos().getX(), (int)transform->getPos().getY(), (int)transform->getH(), (int)transform->getW() },
					transform->getRot(), SDL_Rect{47, 90, 207, 250});
}
