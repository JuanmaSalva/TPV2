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

private:
	Texture* texture;
	int lifes;
};

