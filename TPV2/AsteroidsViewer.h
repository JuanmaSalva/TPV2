#pragma once
#include "Component.h"
#include "AsteroidPool.h"
#include "Entity.h"

class AsteroidsViewer: public Component
{
public:
	AsteroidsViewer();
	virtual ~AsteroidsViewer(){}

	void init() override;
	virtual void draw() override;
private:
	AsteroidPool* asterPool_;
	ObjectPool<Asteroid, 30>* objPool_;
	Texture* texture_;
	vector<Asteroid*> pool;
};

