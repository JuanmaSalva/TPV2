#pragma once
#include "System.h"
#include "Manager.h"
#include "Transform.h"
#include "BulletsSystem.h"

class FighterGunSystem:public System
{
private:
	float time_ = 0;

public:
	FighterGunSystem():System(ecs::_sys_FighterGun){}

	void update() override;
};

