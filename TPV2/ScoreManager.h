#pragma once
#include "Component.h"

class ScoreManager: public Component
{
public:
	ScoreManager():Component(ecs::ScoreManager), puntuacion_(0), parado_(true),terminado_(false){}
	~ScoreManager(){}

	void sumPoints(int p) { puntuacion_ += p; }
	int getPoints() { return puntuacion_; }
	void resetPoints() { puntuacion_ = 0; }
	void setParado(bool p) { parado_ = p; }
	bool getParado() { return parado_; }
	void setTerminado(bool t) { terminado_ = t; }
	bool getTerminado() { return terminado_; }

private:
	int puntuacion_;
	bool parado_;
	bool terminado_;
};

