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

RenderSystem::~RenderSystem()
{
	delete myName_;
	delete otherName_;
}

void RenderSystem::init()
{
	myName_ = new Texture(game_->getRenderer(),
		mngr_->getName(),
		game_->getFontMngr()->getFont(Resources::ARIAL24),
		{ COLOR(0x111122ff) });

	fondo_ = game_->getTextureMngr()->getTexture(Resources::WhiteRect);
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

void RenderSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_CLIENT_DISCONNECTED:
		deleteOtherName();
		break;
	default:
		break;
	}
}

void RenderSystem::setOtherName(const char* name)
{
	otherName_ = new Texture(game_->getRenderer(),
		name,
		game_->getFontMngr()->getFont(Resources::ARIAL24),
		{ COLOR(0x111122ff) });
}

void RenderSystem::deleteOtherName()
{
	delete otherName_;
	otherName_ = nullptr;
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
	if (game_->getNetworking()->getClientId() == 0) {
		if (otherName_ != nullptr) {
			otherName_->render(game_->getWindowWidth() - otherName_->getWidth() - xOffset_, yOffset_);			
		}

		fondo_->render(SDL_Rect{ xOffset_, yOffset_,myName_->getWidth(),myName_->getHeight() });
		myName_->render(xOffset_, yOffset_);
	}
	else {
		if (otherName_ != nullptr) {
			otherName_->render(xOffset_, yOffset_);
		}

		fondo_->render(SDL_Rect{ game_->getWindowWidth() - myName_->getWidth() - xOffset_, yOffset_,myName_->getWidth(),myName_->getHeight() });
		myName_->render(game_->getWindowWidth() - myName_->getWidth() - xOffset_, yOffset_);
	}

}
