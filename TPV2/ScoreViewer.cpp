#include "ScoreViewer.h"
#include "SDL_macros.h"
#include "Entity.h"

ScoreViewer::ScoreViewer(): Component(ecs::ScoreViewer)
{
	scoreManager_ = nullptr;
}

ScoreViewer::~ScoreViewer()
{
}


void ScoreViewer::init()
{
	scoreManager_ = GETCMP1_(ScoreManager);
}

void ScoreViewer::draw()
{
		Texture score(game_->getRenderer(), "Points: " + to_string(scoreManager_->getPoints()), game_->getFontMngr()->getFont(Resources::ARIAL24), SDL_Color{ 230,230,230,255 });
		score.render(game_->getWindowWidth() / 2-30, 20); 

		if (scoreManager_->getTerminado()) { //si ha terminado el juego
			Texture* gameOver = game_->getTextureMngr()->getTexture(Resources::GameOver);

			gameOver->render(game_->getWindowWidth() / 2 - gameOver->getWidth() / 2,
				game_->getWindowHeight() - gameOver->getHeight() - 150);

			if (scoreManager_->getGanado()) {
				Texture win(game_->getRenderer(), "You win", game_->getFontMngr()->getFont(Resources::ARIAL24), SDL_Color{ 230,230,230,255 });
				win.render(game_->getWindowWidth() / 2 - 35, 360);
			}
			else {
				Texture lose(game_->getRenderer(), "You lose", game_->getFontMngr()->getFont(Resources::ARIAL24), SDL_Color{ 230,230,230,255 });
				lose.render(game_->getWindowWidth() / 2 - 35, 360);
			}

		}
}
