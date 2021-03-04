#pragma once

#include "System.h"
#include "Transform.h"
#include "Entity.h"

class PacManSystem: public System {
public:
	PacManSystem();
	void init() override;
	void update() override;
	virtual void recieve(const msg::Message& msg) override;

private:
	Entity *pacman_;
	Transform *tr_;
	int startTime_ = 0;
	int rotationAngle = 10;
	bool green = false;

	void resetPacManPosition();
	void eatenWrongFood();
	void changeSkin(int skin);
};

