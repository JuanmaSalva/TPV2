#pragma once
#include "Component.h"
#include "Transform.h"

class FighterCtrl :
	public Component
{
public:
	FighterCtrl();
	FighterCtrl(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up);
	~FighterCtrl();
	void init() override;
	void update() override;
private:
	SDL_Keycode up_;
	SDL_Keycode left_;
	SDL_Keycode right_;
	Transform* tr_;
};

