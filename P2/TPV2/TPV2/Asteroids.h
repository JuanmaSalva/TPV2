#pragma once

#include <vector>

#include "CollisionSystem.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "PacManSystem.h"
#include "RenderSystem.h"
#include "SDLGame.h"
#include "StarsSystem.h"
#include "FighterSystem.h"

class Asteroids {

public:
	Asteroids();
	virtual ~Asteroids();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();

	void addStars(std::size_t n);

	SDLGame *game_;
	Manager *mngr_;
	GameState* gameState_;
	bool exit_;

	RenderSystem *renderSystem_;
	StarsSystem *starsSystem_;
	PacManSystem *pacmanSystem_;
	CollisionSystem *collisionSystem_;
	GameCtrlSystem *gameCtrlSystem_;
	FighterSystem* fighterSystem_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};
