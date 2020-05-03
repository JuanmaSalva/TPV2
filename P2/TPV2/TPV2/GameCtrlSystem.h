#pragma once

#include "ecs.h"
#include "System.h"
#include "Score.h"
#include "AsteroidsSystem.h"
#include "Health.h"


class GameCtrlSystem: public System {
public:

	GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	}

	void onFighterDeath();
	void onAsteroidsExtenction();

	void init() override;
	void update() override;
	virtual void recieve(const msg::Message& msg);
};

