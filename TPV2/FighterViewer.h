#pragma once
#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class FighterViewer: public Component
{
public:
	FighterViewer();
	virtual ~FighterViewer();
	void init() override;
	void draw() override;
private:
	Texture* texture;
};

