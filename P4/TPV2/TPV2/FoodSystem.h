#pragma once

#include "System.h"

class FoodSystem: public System {
public:
	FoodSystem();
	void init() override;
	void update() override;
	virtual void recieve(const msg::Message& msg);

private:
	int numOfFoodPieces_;

	void addFood(std::size_t n);
	void onEat(Entity *e);
	void disableAll();
};