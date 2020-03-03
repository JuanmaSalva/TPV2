#pragma once
#include "Component.h"
#include "AsteroidPool.h"
#include "BulletsPool.h"
#include "Health.h"
#include "Transform.h"
#include "ScoreManager.h"
#include "Collisions.h"
#include "Asteroid.h"

class GameLogic : public Component
{
public:
	GameLogic(AsteroidPool* a, BulletsPool* b, Health* h, Transform* t);
	~GameLogic(){}

	void init() override;
	void update() override;
private:
	AsteroidPool* asterPool_;
	BulletsPool* bulletsPool_;
	Health* healtzCaza_;
	Transform* trCaza_;
	ScoreManager* scoreMgr_;
	
	vector<Asteroid*> poolAsteroid;
	vector<Bullet*> poolBullets;

	void colisionAsteroidesCaza();
	void colisionBalasAsteroides();
};

