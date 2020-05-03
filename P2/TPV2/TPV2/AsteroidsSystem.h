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

	virtual void init() override;
	virtual void update() override;
	virtual void recieve(const msg::Message& msg);

private:
	int windowWidth_, windowHeight_;
};

