#pragma once

#include "ecs.h"
#include "System.h"
#include "SDLGame.h"
#include "Manager.h"

class GameCtrlSystem : public System {
public:
	enum State : uint8_t {
		READY, RUNNING, ROUNDOVER, GAMEOVER, WAITING
	};

	GameCtrlSystem();
	void init() override;
	void update() override;
	State getState() {
		return state_;
	}
	void onFighterDeath(uint8_t fighterId);
	uint8_t getScore(uint8_t fighterId) {
		assert(fighterId >= 0 && fighterId <= 1);
		return score[fighterId];
	}
	void setStateReady() { state_ = READY; }
	virtual void recieve(const msg::Message& msg);

	bool getWinner() { return winner; };
private:
	void startGame();
	void resetScore();
	void sendMyInfo();
	void onFightersCollide();

	uint8_t score[2];
	State state_;

	bool winner = false;
};

