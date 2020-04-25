#pragma once

#include "ecs.h"
#include "StarsSystem.h"
#include "System.h"
#include "Score.h"
#include "AsteroidsSystem.h"


class GameCtrlSystem: public System {
public:

	GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	}

	void onFighterDeath();
	void onAsteroidsExtenction();

	void init() override;
	void update() override;
};

