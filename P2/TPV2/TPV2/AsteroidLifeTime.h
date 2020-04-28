#pragma once
#include "Component.h"
class AsteroidLifeTime : public Component
{
public:
	AsteroidLifeTime(int gen):Component(ecs::AsteroidLifeTime), generacion(gen){}
	AsteroidLifeTime():AsteroidLifeTime(3){}
	~AsteroidLifeTime(){}

	void SetGen(int gen) { generacion = gen; }
	int GetGen() { return generacion; }
private:
	int generacion; //por que generacion va
};

