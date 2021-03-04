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

	void addFood(std::size_t n, int foodType);
	void onEat(Entity *e, int foodType);
	void disableAll();
};