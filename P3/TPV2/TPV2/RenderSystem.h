#pragma once

#include "Entity.h"
#include "System.h"



class RenderSystem: public System {
public:
	RenderSystem();
	~RenderSystem();

	void init() override;
	void update() override;

	void setOtherName(const char* name);
private:
	void drawImage(Entity* e);
	void drawCtrlMessages();
	void drawScore();
	void drawNames();

	Texture* myName_;
	Texture* otherName_;
	Texture* fondo_;

	int yOffset_ = 20, xOffset_ = 20;
};
