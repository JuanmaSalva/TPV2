#include "RenderSystem.h"

#include "ecs.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "SDL_macros.h"
#include "SDLGame.h"

#include "Image.h"
#include "Transform.h"
#include "Texture.h"

RenderSystem::RenderSystem() :
	System(ecs::_sys_Render) {
}

void RenderSystem::update() {
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullets))
		drawImage(e); // auto cast from unique_ptr to Entity*

	drawCtrlMessages();
	drawScore();
	drawNames();
}

void RenderSystem::drawImage(Entity* e) {
	Transform* tr = e->getComponent<Transform>(ecs::Transform);
	Texture* tex = e->getComponent<Image>(ecs::Image)->tex_;

	SDL_Rect dest =
		RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	tex->render(dest, tr->rotation_);
}

void RenderSystem::drawCtrlMessages() {
	auto gameState =
		mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getState();

	if (gameState == GameCtrlSystem::WAITING) {
		auto msgTex = game_->getTextureMngr()->getTexture(Resources::WaitingForPlayer);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight()) / 2);
	}
	else if (gameState != GameCtrlSystem::RUNNING) {
		auto msgTex = game_->getTextureMngr()->getTexture(
			Resources::PressEnter);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

	if (gameState == GameCtrlSystem::GAMEOVER) {
		auto msgTex = game_->getTextureMngr()->getTexture(Resources::GameOver);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight()) / 2);

		Texture* winText;
		if (mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getWinner())
			winText = game_->getTextureMngr()->getTexture(Resources::YouWin);
		else
			winText = game_->getTextureMngr()->getTexture(Resources::YouLose);

		winText->render((game_->getWindowWidth() - winText->getWidth()) / 2, (game_->getWindowHeight() - winText->getHeight()) / 2 - 100);
	}

}

void RenderSystem::drawScore() {
	auto gameCtrl = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	Texture scoreTex(game_->getRenderer(),
		to_string(gameCtrl->getScore(0)) + " - "
		+ to_string(gameCtrl->getScore(1)),
		game_->getFontMngr()->getFont(Resources::ARIAL24),
		{ COLOR(0x111122ff) });
	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);
}

void RenderSystem::drawNames()
{
	auto gameCtrl = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);
	int yOffset = 20, xOffset = 20;

	if (game_->getNetworking()->getClientId() == 0) {
		Texture myName(game_->getRenderer(),
			mngr_->getName(),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });

		const char* otherName = gameCtrl->getOtherName();
		if (otherName != nullptr) {
			Texture otherName(game_->getRenderer(),
				otherName,
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0x111122ff) });
			otherName.render(game_->getWindowWidth() - otherName.getWidth() - xOffset, yOffset);
		}

		Texture* fondo = game_->getTextureMngr()->getTexture(Resources::WhiteRect);

		fondo->render(SDL_Rect{ xOffset, yOffset,myName.getWidth(),myName.getHeight() });
		myName.render(xOffset, yOffset);
	}
	else {
		Texture myName(game_->getRenderer(),
			mngr_->getName(),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });


		const char* otherName = gameCtrl->getOtherName();
		if (otherName != nullptr) {
			Texture otherName(game_->getRenderer(),
				otherName,
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0x111122ff) });
			otherName.render(xOffset, yOffset);
		}

		Texture* fondo = game_->getTextureMngr()->getTexture(Resources::WhiteRect);
		fondo->render(SDL_Rect{ game_->getWindowWidth() - myName.getWidth() - xOffset, yOffset,myName.getWidth(),myName.getHeight() });

		myName.render(game_->getWindowWidth() - myName.getWidth() - xOffset, yOffset);
	}

}
