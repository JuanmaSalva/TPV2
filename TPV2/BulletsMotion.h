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
	vector<Bullet*> pool;
	BulletsPool* bulletsPool_;
	ObjectPool<Bullet, 10>* objPool_;
};

