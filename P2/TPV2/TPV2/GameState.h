#pragma once
#include "Component.h"
class GameState:public Component
{
public:
	GameState():Component(ecs::GameState), parado(true), terminado(false){}
	~GameState(){}

	void setParado(bool p) { parado = p; }
	void setTerminado(bool t) { terminado = t; }
	void setGanador(bool g) { winner_ = g; }

	bool getParado() { return parado; }
	bool getTerminado() { return terminado; }
	bool getGanador() { return winner_; }
private:
	bool parado, terminado;
	bool winner_ = false;
};

