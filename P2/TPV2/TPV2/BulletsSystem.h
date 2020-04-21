#pragma once
#include "System.h"
#include "Vector2D.h"
#include "Entity.h"

class BulletsSystem :public System
{
public:
	//BulletsSystem():System(ecs::_sys_Bullets){}

	void shoot(Vector2D pos, Vector2D vel, double width, double height);
	void onCollisionWithAsteroid(Entity* bullet, Entity* asteroid);

	void update() override;

private:
};

