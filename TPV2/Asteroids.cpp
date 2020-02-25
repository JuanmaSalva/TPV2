#include "SDL_macros.h"
#include "Asteroids.h"
#include <assert.h>

#include "BallMoveBehaviour.h"
#include "GameCtrl.h"
#include "GameLogic.h"
#include "InputHandler.h"
#include "PaddleKBCtrl.h"
#include "PaddleMouseCtrl.h"
#include "PaddleMoveBehaviour.h"
#include "Rectangle.h"
#include "ScoreManager.h"
#include "ScoreViewer.h"
#include "SimpleMoveBahviour.h"
#include "Transform.h"
#include "SDLGame.h"
#include "FighterViewer.h"
#include "FighterCtrl.h"
#include "Health.h"
#include "FighterMotion.h"
#include "Bullet.h"
#include "BulletsPool.h"
#include "BulletsMotion.h"
#include "BulletsViewer.h"
#include "Gun.h"

#include "SDL_macros.h"

using namespace std;

Asteroids::Asteroids() :
		game_(nullptr), //
		entityManager_(nullptr), //
		exit_(false) {
	initGame();
}

Asteroids::~Asteroids() {
	closeGame();
}

void Asteroids::initGame() {

	game_ = SDLGame::init("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	Entity* caza = entityManager_->addEntity();
	Transform* cazaTR = caza->addComponent<Transform>();
	cazaTR->setPos(game_->getWindowWidth() / 2,	game_->getWindowHeight() / 2);
	cazaTR->setWH(50, 50);
	cazaTR->setSpeeddLimit(4);
	cazaTR->setThrust(0.5);
	caza->addComponent<FighterViewer>();
	caza->addComponent<Health>();
	caza->addComponent<FighterCtrl>();	
	caza->addComponent<FighterMotion>(0.98);
	caza->addComponent<BulletsPool>();
	caza->addComponent<BulletsMotion>();
	caza->addComponent<BulletsViewer>();
	caza->addComponent<Gun>();
		
	//crea el game manager pero no lo mete a ningun lado xq ya se mete en una lista de entities en el entitymanager
	Entity* gameManager = entityManager_->addEntity();
	gameManager->addComponent<GameLogic>(); 
}

void Asteroids::closeGame() {
	delete entityManager_;
}

void Asteroids::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Asteroids::stop() {
	exit_ = true;
}

void Asteroids::handleInput() {

	InputHandler *ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			} else {
				SDL_SetWindowFullscreen(game_->getWindow(),
						SDL_WINDOW_FULLSCREEN);
			}
		}
	}

}

void Asteroids::update() {
	entityManager_->update();
}

void Asteroids::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}

