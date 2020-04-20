#include "GameCtrlSystem.h"

void GameCtrlSystem::init(){
	Entity* e = mngr_->addEntity();
	auto sc = e->addComponent<Score>();
	sc->points_ = 0;
	mngr_->setHandler(ecs::_hdlr_GameState, e);
}

void GameCtrlSystem::update(){
	auto ih = game_->getInputHandler();

	/*if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
		mngr_->getSystem<StarsSystem>(ecs::_sys_Stars)->addStars(10);
	}*/
}

void GameCtrlSystem::onFighterDeath()
{
}

void GameCtrlSystem::onAsteroidsExtenction()
{
}