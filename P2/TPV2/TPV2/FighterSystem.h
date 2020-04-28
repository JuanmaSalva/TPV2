#pragma once
#include "System.h"
#include "Entity.h"
#include "Transform.h"
#include "Manager.h"
#include "ImageComponent.h"
#include "Health.h"
#include "GameCtrlSystem.h"

class FighterSystem:public System
{
public:
	FighterSystem(double drag, int fw, int fh):System(ecs::_sys_Fighter),fighter_(nullptr),tr_(nullptr), drag_(drag),
	fighterWidth_(fw), fighterHeight_(fh){
	}

	void init() override;
	void update() override;
	virtual void recieve(const msg::Message& msg) override;

private:
	Entity* fighter_;
	Transform* tr_;
	double drag_ = 0.0;
	int window_width = 640, window_height = 480;
	int fighterWidth_, fighterHeight_;
};

