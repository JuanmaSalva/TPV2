#pragma once
#include "Component.h"
#include "AsteroidPool.h"
#include "Health.h"
#include "ScoreManager.h"
#include "Entity.h"
#include "Texture.h"

class GameCtrl :public Component
{
public:
	GameCtrl(AsteroidPool* a, Health* h);
	~GameCtrl() {}

	void init()override;
	void update()override;
	void draw() override;


private:
	AsteroidPool* asterPool_;
	Health* healthCaza_;
	ScoreManager* scoreManager;
};

