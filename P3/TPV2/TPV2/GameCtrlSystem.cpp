#include "GameCtrlSystem.h"

#include <cassert>
#include <cstdint>
#include "ecs.h"
#include "Entity.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "Manager.h"

using ecs::CmpId;

GameCtrlSystem::GameCtrlSystem() :
	System(ecs::_sys_GameCtrl) {
	state_ = WAITING;
	resetScore();
}

void GameCtrlSystem::init() {
}

void GameCtrlSystem::update() {
	if (state_ != RUNNING) {
		InputHandler* ih = game_->getInputHandler();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			if (game_->getNetworking()->getClientId() == 1)mngr_->send<msg::Message>(msg::_ASK_GAME_TO_START); //pedir q empiece el juego
			else {
				mngr_->send<msg::Message>(msg::_GAME_STARTED);
				startGame();
			}
		}
	}
}

void GameCtrlSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_GAME_STARTED:
		startGame();
		break;
	case msg::_SECOND_PLAYER_JOINED:
		setStateReady();
		break;
	case msg::_ASK_GAME_TO_START:
		mngr_->send<msg::Message>(msg::_GAME_STARTED);
		startGame();
		break;
	default:
		break;
	}
}

void GameCtrlSystem::startGame() {
	if (state_ == GAMEOVER) {
		resetScore();
	}
	mngr_->getSystem<FightersSystem>(ecs::_sys_Fighters)->resetFighterPositions();
	state_ = RUNNING;

}

void GameCtrlSystem::onFighterDeath(uint8_t fighterId) {
	assert(fighterId >= 0 && fighterId <= 1);

	uint8_t id = 1 - fighterId; // the id of the other player fighter

	state_ = ROUNDOVER;
	score[id]++;
	if (score[id] == 3)
		state_ = GAMEOVER;

}

void GameCtrlSystem::resetScore() {
	score[0] = score[1] = 0;
}
