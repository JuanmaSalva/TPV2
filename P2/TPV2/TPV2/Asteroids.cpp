#include "SDL_macros.h"
#include "Asteroids.h"
#include <assert.h>

#include "ImageComponent.h"
#include "InputHandler.h"
#include "Transform.h"
#include "SDLGame.h"

#include "SDL_macros.h"
#include "StarsSystem.h"
#include "StarsPool.h"

using namespace std;

Asteroids::Asteroids() :
		game_(nullptr), //
		mngr_(nullptr), //
		exit_(false) {
	initGame();
}

Asteroids::~Asteroids() {
	closeGame();
}

void Asteroids::initGame() {

	game_ = SDLGame::init("Stars", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);
	gameState_ = new GameState();

	StarsPool::init(100);

	mngr_ = new Manager(game_, gameState_);

	renderSystem_ = mngr_->addSystem<RenderSystem>();
	starsSystem_ = mngr_->addSystem<StarsSystem>();
	pacmanSystem_ = mngr_->addSystem<PacManSystem>();
	collisionSystem_ = mngr_->addSystem<CollisionSystem>();
	gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
	fighterSystem_ = mngr_->addSystem<FighterSystem>(0.95);
}

void Asteroids::closeGame() {
	delete mngr_;
	delete gameState_;
}

void Asteroids::start() {
	exit_ = false;
	auto ih = InputHandler::instance();
	while (!exit_) {
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());
		Uint32 startTime = game_->getTime();

		ih->update();
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_ESCAPE)) {
				exit_ = true;
				break;
			}
		}

		mngr_->refresh();

		gameCtrlSystem_->update();
		starsSystem_->update();
		pacmanSystem_->update();
		collisionSystem_->update();
		renderSystem_->update(); //todos los renders de las enteties
		fighterSystem_->update();


		SDL_RenderPresent(game_->getRenderer());

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}


