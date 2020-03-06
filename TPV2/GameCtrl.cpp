#include "GameCtrl.h"

GameCtrl::GameCtrl(AsteroidPool* a, Health* h):Component(ecs::GameCtrl)
{
	asterPool_ = a;
	healthCaza_ = h;
}

void GameCtrl::init()
{
	scoreManager = GETCMP1_(ScoreManager);
}

void GameCtrl::update()
{
	if (InputHandler::instance()->keyDownEvent()) {
		if (scoreManager->getParado()) { //si el estado estaba parado
			//activar el juego
			asterPool_->generateAsteroids(1);
			scoreManager->setParado(false);
			scoreManager->setTerminado(false);
			scoreManager->setGanado(false);
		}
	}

	if (scoreManager->getTerminado()) {
		healthCaza_->resetLife();
		scoreManager->resetPoints();
	}
}

void GameCtrl::draw()
{
	if (scoreManager->getParado()) { //si esta parado
		Texture* hitanykey = game_->getTextureMngr()->getTexture(Resources::PressAnyKey);

		hitanykey->render(game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2, //pone la posicion
			game_->getWindowHeight() - hitanykey->getHeight() - 50);
	}
}
