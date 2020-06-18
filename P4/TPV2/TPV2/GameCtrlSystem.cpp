#include "GameCtrlSystem.h"

#include "FoodSystem.h"
#include "SDLGame.h"
#include "Manager.h"
#include "GameState.h"
#include "GhostsSystem.h"
#include "PacManSystem.h"
#include "messages.h"


GameCtrlSystem::GameCtrlSystem() :
		System(ecs::_sys_GameCtrl), //
		gameState_(nullptr) {
}


void GameCtrlSystem::init() {
	Entity *e = mngr_->addEntity();
	gameState_ = e->addComponent<GameState>();
	mngr_->setHandler(ecs::_hdlr_GameStateEntity, e);
	mngr_->send <msg::PlayMusic>(Resources::PacMan_Intro);
	//game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
}

void GameCtrlSystem::update() {

	if ( gameState_->state_ == GameState::RUNNING )
		return;

	auto ih = game_->getInputHandler();

	if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
		switch ( gameState_->state_) {
		case GameState::READY:
			gameState_->state_ = GameState::RUNNING;
			game_->getAudioMngr()->haltMusic();
			startGame();
			break;
		case GameState::OVER:
			gameState_->state_ = GameState::READY;
			gameState_->score_ = 0;
			gameState_->won_ = false;

			mngr_->send<msg::PlayMusic>(Resources::PacMan_Intro);
			//game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
			break;
		default:
			assert(false); // should not be rechable
			break;
		}
	}
}

void GameCtrlSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_PAC_MAN_DEATH:
		onPacManDeath();
		break;
	case msg::_NO_MORE_FOOD:
		onNoMoreFood();
		break;
	default:
		break;
	}
}

void GameCtrlSystem::onPacManDeath() {
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = false;
	mngr_->send<msg::Message>(msg::_DISABLE_GHOST);
	mngr_->send<msg::Message>(msg::_DISABLE_CHERRIES);
	//game_->getAudioMngr()->haltMusic();
	mngr_->send<msg::Message>(msg::_HALT_MUSIC);
	mngr_->send<msg::PlayChannel>(Resources::PacMan_Death, 0);
	//game_->getAudioMngr()->playChannel(Resources::PacMan_Death,0);
}

void GameCtrlSystem::onNoMoreFood() {
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = true;
	mngr_->send<msg::Message>(msg::_DISABLE_GHOST);
	mngr_->send<msg::Message>(msg::_DISABLE_CHERRIES);
	//game_->getAudioMngr()->haltMusic();
	mngr_->send<msg::Message>(msg::_HALT_MUSIC);
	mngr_->send<msg::PlayChannel>(Resources::PacMan_Won, 0);
	//game_->getAudioMngr()->playChannel(Resources::PacMan_Won,0);
}

void GameCtrlSystem::startGame() {
	mngr_->send<msg::Message>(msg::_GAME_START);
	mngr_->send<msg::SingleIntMessage>(10, msg::_ADD_FOOD);
	mngr_->send<msg::SingleIntMessage>(2, msg::_ADD_GHOST);
	mngr_->send<msg::Message>(msg::_RESET_PACMAN_POS);
}
