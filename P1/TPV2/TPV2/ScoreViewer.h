#pragma once
#include "Component.h"
#include "ScoreManager.h"

class ScoreViewer :
	public Component
{
public:
	ScoreViewer();
	~ScoreViewer();
	void init() override;
	void draw() override;

private:
	ScoreManager* scoreManager_;
};

