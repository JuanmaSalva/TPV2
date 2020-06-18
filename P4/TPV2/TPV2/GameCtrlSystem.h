#pragma once

#include "System.h"

struct GameState;

class GameCtrlSystem: public System {
public:

	GameCtrlSystem();

	void init() override;
	void update() override;
	virtual void recieve(const msg::Message& msg) override;


private:
	void startGame();
	void onPacManDeath();
	void onNoMoreFood();

	GameState *gameState_;

};

