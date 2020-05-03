#include "GameCtrlSystem.h"

void GameCtrlSystem::init(){
	Entity* e = mngr_->addEntity();
	auto sc = e->addComponent<Score>();
	sc->points_ = 0;
	mngr_->setHandler(ecs::_hdlr_GameState, e);

	game_->getAudioMngr()->playMusic(Resources::imperial_march,-1);
	game_->getAudioMngr()->pauseMusic();
}

void GameCtrlSystem::update(){
	auto ih = game_->getInputHandler();

	if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN) && mngr_->getGameState()->getParado()) {
		
		mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->addAsteroids(10);
		mngr_->getGameState()->setParado(false);
		mngr_->getGameState()->setTerminado(false);
		mngr_->getGameState()->setGanador(false);
		game_->getAudioMngr()->resumeMusic();
	}
}

void GameCtrlSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_FIGHTERASTEROID_COLLISION_: {
		mngr_->getGameState()->setParado(true);
		break;
	}
	default:
		break;
	}
}

void GameCtrlSystem::onFighterDeath()
{
	//resertea todo
	mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score)->points_ = 0;
	mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Health>(ecs::Health)->setHealth(3);
	mngr_->getGameState()->setTerminado(true);
	mngr_->getGameState()->setParado(true);
}

void GameCtrlSystem::onAsteroidsExtenction()
{
	mngr_->getGameState()->setTerminado(true);
	mngr_->getGameState()->setParado(true);
	mngr_->getGameState()->setGanador(true);
}