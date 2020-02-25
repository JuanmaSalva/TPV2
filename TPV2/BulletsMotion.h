#pragma once
#include "Component.h"
#include "BulletsPool.h"
#include "Entity.h"

class BulletsMotion : public Component
{
public:
	BulletsMotion();
	~BulletsMotion();

	void init() override;
	virtual void update() override;

private:

	BulletsPool* bulletsPool_;
	ObjectPool<Bullet, 10>* objPool_;

	//lo he copiado de asteroids.h pero no tiene sentido q alli sean privadas
	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;
};

