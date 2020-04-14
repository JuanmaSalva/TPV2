#include "Health.h"
Health::Health() :
	Component(ecs::Health) //llama a la constructora de arriba diciendo lo que es
{
}

Health::~Health()
{
}

void Health::init()
{
	texture = game_->getTextureMngr()->getTexture(10); //esto del 10 se tiene que poder hacer de otra manera
	lifes = 3;
}

void Health::draw()
{
	for (int i = 0; i < lifes; i++) {
		texture->render(SDL_Rect{ 10+(35*i), 10, 30, 30 }); //el 35*i es una manera de espaciarlos horizontalmente
	}
}

void Health::loseLife()
{
	lifes -= 1;
}

void Health::resetLife()
{
	lifes = 3;
}
