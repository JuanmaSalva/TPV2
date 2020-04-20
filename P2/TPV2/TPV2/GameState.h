#pragma once
#include "Component.h"
class GameState:public Component
{
public:
	GameState():Component(ecs::GameState), parado(false), terminado(false){}
	~GameState(){}

	void setParado(bool p) { parado = p; }
	void setTerminado(bool t) { terminado = t; }

	bool getParado() { return parado; }
	bool getTerminado() { return terminado; }
private:
	bool parado, terminado;
	//GANADOR
};

