#include "FighterViewer.h"

FighterViewer::FighterViewer() :
	Component(ecs::Fighter)
{
	texture = game_->getTextureMngr()->getTexture(ecs::Fighter);
}

FighterViewer::~FighterViewer()
{
}

void FighterViewer::init()
{
}

void FighterViewer::draw()
{

	cout << "Llega";
}
