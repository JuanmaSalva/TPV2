#pragma once
#include "System.h"


class FighterGun:public System
{
public:
	//FighterGun() :System(ecs::_sys_FighterGun){}

	void update() override;
};

