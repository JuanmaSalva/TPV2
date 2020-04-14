#pragma once
#include "Component.h"

class Health:public Component
{
public:
	Health();
	~Health();

	void init() override;
	void draw() override;

	void loseLife();
	void resetLife();
	int getLife() { return lifes; }

private:
	Texture* texture;
	int lifes;
};

