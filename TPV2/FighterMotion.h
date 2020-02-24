#pragma once
#include "Component.h"
#include "Transform.h"

class FighterMotion :
	public Component
{
public:
	FighterMotion(double drag);
	~FighterMotion();
	void init() override;
	void update() override;

private:
	Transform* tr_ = nullptr;
	double drag_ = 0.0;
};

