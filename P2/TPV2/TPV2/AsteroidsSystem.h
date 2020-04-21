#pragma once
#include "System.h"
#include "Entity.h"

class AsteroidsSystem:public System
{
public:
	//AsteroidsSystem():System(ecs::_sys_Asteroids){}

	void addAsteroids(int n){}
	void onCollisionWithBullet(Entity* asteroid, Entity* bullet);

	void update() override;

private:
	std::size_t numOfAsteroids_;
};

