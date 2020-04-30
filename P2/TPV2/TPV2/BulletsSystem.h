#pragma once
#include "System.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Manager.h"
#include "BulletPool.h"

class BulletsSystem :public System
{
public:
	BulletsSystem():System(ecs::_sys_Bullets){}

	void shoot(Vector2D pos, Vector2D vel, double width, double height);
	void onCollisionWithAsteroid(Entity* bullet, Entity* asteroid);

	virtual void init() override;
	virtual void update() override;
	virtual void recieve(const msg::Message& msg) override;

private:
	int windowWidth_, windowHeight_;
};

