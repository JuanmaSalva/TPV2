#pragma once
#include "System.h"
#include "Entity.h"

class Fighter:public System
{
public:
	Fighter():System(ecs::_sys_Fighter){}

	void onCollisionWithAsteroid(Entity* asteroid);

	void init() override;
	void update() override;
};

