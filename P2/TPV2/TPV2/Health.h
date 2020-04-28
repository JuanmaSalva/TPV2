#pragma once
#include "Component.h"
class Health:public Component
{
public:
	Health(int h):Component(ecs::Health), lives(h){}

	void setHealth(int h) { lives = h; }
	bool removeLife() { 
		lives--; 
		if (lives > 0) return true;
		else return false;
	}

	int getHealth() { return lives; }

	
private:
	int lives;
};

