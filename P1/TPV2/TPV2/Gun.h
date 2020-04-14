#pragma once
#include "Component.h"
#include "BulletsPool.h"
#include "InputHandler.h"
#include "Transform.h"

class Gun: public Component
{
public:
	Gun();
	Gun(SDL_Keycode shoot);
	~Gun();

	void init() override;
	void update() override;
private:
	SDL_Keycode shoot_;
	BulletsPool* bulletsPool_ = nullptr;
	Transform* tr_ = nullptr;

	float time_ = 0;
};

