#pragma once
#include "Component.h"
#include "BulletsPool.h"

class BulletsViewer: public Component
{
public:
	BulletsViewer(BulletsPool* b);
	~BulletsViewer();

	virtual void draw() override;

private:
	BulletsPool* bulletsPool_;
	ObjectPool<Bullet, 10>* objPool_;
};

