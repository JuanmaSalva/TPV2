#pragma once
#include "Component.h"
#include "BulletsPool.h"
#include "Entity.h"

class BulletsViewer: public Component
{
public:
	BulletsViewer();
	~BulletsViewer();

	void init() override;
	virtual void draw() override;
private:
	BulletsPool* bulletsPool_;
	ObjectPool<Bullet, 10>* objPool_;
	Texture* texture;
};

