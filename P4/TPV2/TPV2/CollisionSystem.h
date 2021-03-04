#pragma once

#include "System.h"
#include "Transform.h"

class CollisionSystem: public System {
public:
	CollisionSystem();

	void update() override;
	void collision(Entity* e,Transform* ptr,  int foodType);

};

