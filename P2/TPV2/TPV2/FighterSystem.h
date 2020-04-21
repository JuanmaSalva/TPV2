#pragma once
#include "System.h"
#include "Entity.h"
#include "Transform.h"
#include "Manager.h"
#include "ImageComponent.h"

class FighterSystem:public System
{
public:
	FighterSystem(double drag):System(ecs::_sys_Fighter),fighter_(nullptr),tr_(nullptr), drag_(drag){}

	void onCollisionWithAsteroid(Entity* asteroid);

	void init() override;
	void update() override;

private:
	Entity* fighter_;
	Transform* tr_;
	double drag_ = 0.0;
};

