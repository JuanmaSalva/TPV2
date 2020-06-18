#pragma once

#include "System.h"
#include <SDL.h>

class GhostsSystem: public System {
public:
	GhostsSystem();
	void init() override;
	void update() override;
	virtual void recieve(const msg::Message& msg) override;

private:
	Uint32 lastTimeAdded_;
	int maxGhosts_;
	int numOfGhosts_;

	void onCollisionWithPacMan();
	void addGhosts(std::size_t n);
	void disableAll();
};

