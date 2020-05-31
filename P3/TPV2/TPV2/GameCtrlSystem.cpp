#include "GameCtrlSystem.h"

#include <cassert>
#include <cstdint>
#include "ecs.h"
#include "Entity.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "Manager.h"
#include "BulletsSystem.h"
#include "RenderSystem.h"

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
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN) && state_ != WAITING) {
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
	case msg::_FIGHTER_COLLISION: {
		if (game_->getNetworking()->getClientId() == 1) {
			const msg::FighterCollision& m = static_cast<const msg::FighterCollision&>(msg);
			onFighterDeath(m.fighterId);
			mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();
		}
		break;
	}
	case msg::_FIGHTERS_COLLIDE:
		std::cout << "Fighter collide msg" << endl;
		onFightersCollide();
		break;
	case msg::_NAME: {
		const msg::NameMessage& m = static_cast<const msg::NameMessage&>(msg);
		if (m.senderClientId != game_->getNetworking()->getClientId()) {
			mngr_->setOtherName((char*)m.name);
			std::cout << "Hola don " << m.name << endl;

			mngr_->getSystem<RenderSystem>(ecs::_sys_Render)->setOtherName(m.name);
		}
		break;
	}
	case msg::_CLIENT_DISCONNECTED:
		resetScore();
		game_->getNetworking()->setClientId(0);
		state_ = WAITING;
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
	{
		state_ = GAMEOVER;
		if (game_->getNetworking()->getClientId() == (int)id) {
			winner = true;
		}
	}
}

void GameCtrlSystem::onFightersCollide()
{
	state_ = ROUNDOVER;
}

void GameCtrlSystem::resetScore() {
	score[0] = score[1] = 0;
	winner = false;
}
