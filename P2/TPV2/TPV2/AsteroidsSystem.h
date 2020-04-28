#pragma once
#include "System.h"
#include "Entity.h"
#include "AsteroidsPool.h"
#include "Manager.h"

class AsteroidsSystem: public System
{
public:
	AsteroidsSystem():System(ecs::_sys_Asteroids){

	}

	void addAsteroids(int n);
	void onCollisionWithBullet(Entity* asteroid, Entity* bullet);

	virtual void init() override;
	virtual void update() override;
	virtual void recieve(const msg::Message& msg);

private:
	std::size_t numOfAsteroids_;
	int windowWidth_, windowHeight_;
};

